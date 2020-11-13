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

    struct BaseObj {
        BaseType type_;
        Method method_;
    };

    class CommunicationManager { // singleton
      public:
        ~CommunicationManager() noexcept = default;
        static CommunicationManager &Get()
        {
            return instance_;
        };

        Buffer serialize(BaseType type, Method method) //encode Package
        {
            size_t lengthBuffer = 2;
            Buffer buffer(lengthBuffer, 0); // We prefill the buffer of lengthBuffer 0

            // In the first byte we store the type and the methods
            buffer[DEFINITON_BYTE] = (method << 6) + type; // Since type and enum are enums having less than 15 members each we can simply use bitshft to store it in 1 byte;
            buffer[1] = '\n';
            return buffer;
        };

        BaseObj deserialize(const Buffer &buffer) //decode Package
        {
            BaseObj obj = {
                .type_ = static_cast<BaseType>(buffer[DEFINITON_BYTE] & 0xF),
                .method_ = static_cast<Method>(buffer[DEFINITON_BYTE] >> 4)
            };
            return obj;
        };

      private:
        CommunicationManager();

      private:
        static CommunicationManager instance_;
    };
};

namespace rtype {
    namespace BPC = BinaryProtocolCommunication;
};
