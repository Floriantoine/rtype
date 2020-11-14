/*
** EPITECH PROJECT, 2020
** core
** File description:
** BPC
*/

#pragma once

#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>

#define ARG_START 3
#define HEADER_SIZE 23
#define DEFINITON_BYTE 0
#define PEER_INFO DEFINITON_BYTE + 17

namespace rtype::BinaryProtocolCommunication {
    typedef std::vector<unsigned char> Buffer; // binary to send

    enum BaseType {
        REQUEST,
        RESPONSE,
        OTHER
    };

    enum Method {
        CREATE,
        JOIN,
        LIST,
        SPAWN, // Create
        MOVE, // position
        DESTROY,
        SCORE,
    };

    struct Endpoint {
        std::string ip;
        std::uint16_t port;
    };

    struct Package {
        BaseType type;
        Method method;
        unsigned long timestamp;
        Endpoint endpoint;
        Buffer body;
    };

    class CommunicationManager { // singleton
      private:
        CommunicationManager() = default;

      public:
        ~CommunicationManager() noexcept = default;
        static CommunicationManager &Get()
        {
            static CommunicationManager instance;

            return instance;
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
            Buffer buffer(HEADER_SIZE, 0);

            buffer[DEFINITON_BYTE] = (package.method << 6) + package.type;
            EncodePeerInfos(buffer, package.endpoint);
            return buffer;
        };

        static Package Deserialize(const Buffer &buffer)
        {
            const Package obj = {
                .type = static_cast<BaseType>(buffer[DEFINITON_BYTE] & 0xF),
                .method = static_cast<Method>(buffer[DEFINITON_BYTE] >> 4)
            };
            DecodePeerInfos(buffer);
            return obj;
        };
    };
};

namespace rtype {
    namespace BPC = BinaryProtocolCommunication;
};
