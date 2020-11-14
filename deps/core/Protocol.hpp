/*
** EPITECH PROJECT, 2020
** core
** File description:
** BPC
*/

#pragma once

#include <vector>

#define ARG_START 3
#define DEFINITON_BYTE 0
#define PEER_INFO DEFINITON_BYTE + 1

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

    struct Package {
        BaseType type_;
        Method method_;
        Buffer body_;
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

        static Buffer serialize(BaseType type, Method method)
        {
            size_t lengthBuffer = 2;
            Buffer buffer(lengthBuffer, 0);

            buffer[DEFINITON_BYTE] = (method << 6) + type;
            buffer[1] = '\n';
            return buffer;
        };

        static Package deserialize(const Buffer &buffer)
        {
            const Package obj = {
                .type_ = static_cast<BaseType>(buffer[DEFINITON_BYTE] & 0xF),
                .method_ = static_cast<Method>(buffer[DEFINITON_BYTE] >> 4)
            };
            return obj;
        };
    };
};

namespace rtype {
    namespace BPC = BinaryProtocolCommunication;
};
