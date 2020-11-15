/*
** EPITECH PROJECT, 2020
** core
** File description:
** BPC
*/

#pragma once

#include "utils/Clock.hpp"

#include <bits/c++config.h>
#include <boost/algorithm/string.hpp>
#include <cassert>
#include <functional>
#include <string>
#include <vector>

#define DEFINITON_BYTE 0
#define BODY_SIZE (DEFINITON_BYTE + 1)
#define TIMESTAMP (BODY_SIZE + sizeof(unsigned long))
#define BODY (TIMESTAMP + sizeof(long))
#define HEADER_SIZE BODY
#define PEER_INFO DEFINITON_BYTE + 17

namespace rtype::BinaryProtocolCommunication {
    typedef std::vector<unsigned char> Buffer; // binary to send

    enum BaseType {
        REQUEST,
        RESPONSE,
        OTHER
    };

    enum Method {
        ASK_JOIN,
        CREATE,
        GAME_STATE,
        MOVE,
        SPAWN,
        DESTROY,
        GRAB,
        DROP,
        CHARGE,
        SHOOT,
        HIT,
        JOIN,
        LEAVE
    };

    struct Endpoint {
        std::string ip;
        std::uint16_t port;

        bool operator==(const Endpoint &other) const
        {
            return this->ip == other.ip && this->port && other.port;
        }
    };

    struct Package {
        BaseType type { REQUEST };
        Method method { ASK_JOIN };
        unsigned long bodySize { 0 };
        long timestamp { 0 };
        Buffer body;

        Package() = default;
        ~Package() = default;

        Package(const Package &other, BaseType type)
            : type { type }
            , method { other.method }
            , timestamp { other.timestamp }
        { }

        Package(const Package &other)
            : type { other.type }
            , method { other.method }
            , timestamp { other.timestamp }
            , bodySize { other.bodySize }
            , body { other.body }
        { }

        Package &operator=(const Package &other)
        {
            this->type = other.type;
            this->method = other.method;
            this->timestamp = other.timestamp;
            this->bodySize = other.bodySize;
            this->body = other.body;
            return *this;
        }

        template <typename T>
        const T *getBodyTo() const
        {
            assert(sizeof(T) == this->body.size());
            return reinterpret_cast<const T *>(this->body.data());
        }

        template <typename T>
        void setBodyFrom(const T *src)
        {
            const unsigned char *buffer = reinterpret_cast<const unsigned char *>(src);

            this->bodySize = sizeof(T);
            this->body.resize(sizeof(T));
            for (auto i = 0u; i < sizeof(T); ++i) {
                this->body[i] = buffer[i];
            }
        }
    };

    static void EncodePeerInfos(Buffer &buffer, const Endpoint &endpoint)
    {
        std::vector<std::string> str_vec_ip;
        boost::split(str_vec_ip, endpoint.ip, boost::is_any_of("."));
        int count = PEER_INFO;

        for (const auto &str : str_vec_ip) {
            buffer[count] = static_cast<unsigned char>(std::atoi(str.c_str()));
            count += 1;
        }
        buffer[count] = (endpoint.port & 0xFF00) >> 8;
        buffer[count + 1] = (endpoint.port & 0xFF);
    };

    static Endpoint DecodePeerInfos(const Buffer &buffer)
    {
        Endpoint endpoint;
        std::vector<std::string> tmp;
        std::uint8_t index = PEER_INFO;
        std::uint8_t i = 0;

        while (i < 4) {
            tmp.emplace_back(std::string((char *)&buffer[index++]));
            ++i;
        }
        endpoint.ip = boost::algorithm::join(tmp, ".");
        endpoint.port = (buffer[index++] | 0xFF00) << 8;
        endpoint.port = buffer[index] | 0xFF;
        return endpoint;
    };

    static Buffer Serialize(const Package &package)
    {
        Buffer buffer(HEADER_SIZE + package.body.size());
        auto biteshift = [&buffer](unsigned offset, unsigned long value) {
            buffer[offset] = (value >> 24 & 0xFF);
            buffer[offset + 1] = (value >> 16 & 0xFF);
            buffer[offset + 2] = (value >> 8 & 0xFF);
            buffer[offset + 3] = (value & 0xFF);
        };

        buffer[DEFINITON_BYTE] = (package.type << 6) + package.method;
        biteshift(BODY_SIZE, package.body.size());
        biteshift(TIMESTAMP, package.timestamp);

        unsigned offset = BODY;
        const unsigned char *body = package.body.data();
        for (unsigned idx = 0; idx < package.body.size(); ++idx) {
            buffer[offset] = body[idx];
            ++offset;
        }
        return buffer;
    };

    static void Deserialize(Package &package, const Buffer &buffer)
    {
        auto rev_bitshift = [&buffer](unsigned long offset) {
            unsigned long value = 0;
            value += (buffer[offset] << 24);
            value += (buffer[offset + 1] << 16);
            value += (buffer[offset + 2] << 8);
            value += (buffer[offset + 3]);
            return value;
        };

        package.type = static_cast<BaseType>(buffer[DEFINITON_BYTE] >> 6);
        package.method = static_cast<Method>(buffer[DEFINITON_BYTE] & 0xF);
        package.bodySize = rev_bitshift(BODY_SIZE);
        package.timestamp = rev_bitshift(TIMESTAMP);
        package.body.clear();
        package.body.reserve(package.bodySize);
        for (unsigned long i = 0; i < package.bodySize; ++i) {
            package.body[i] = buffer[i + HEADER_SIZE];
        }
    };

    static Package Deserialize(const Buffer &buffer)
    {
        Package package;
        Deserialize(package, buffer);
        return package;
    }
};

namespace rtype {
    namespace BPC = BinaryProtocolCommunication;
};
