/*
** EPITECH PROJECT, 2020
** core
** File description:
** BPC
*/

#ifndef BPC_HPP_
#define BPC_HPP_

#include <cstdlib>
#define ARG_START 3
#define DEFINITON_BYTE 0
#define PEER_INFO DEFINITON_BYTE + 1

#include <boost/algorithm/string.hpp>
#include <iostream>
#include <queue>
#include <string>
#include <string_view>
#include <vector>

namespace BinaryProtocolCommunication {
    using Buffer = std::vector<unsigned char>; // binary to send
    namespace BPC = BinaryProtocolCommunication;

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
        static CommunicationManager Get()
        {
            return instance_;
        };

        BPC::Buffer serialize(BPC::BaseType type, BPC::Method method) //encode Package
        {
            size_t lengthBuffer = 2;
            BPC::Buffer buffer(lengthBuffer, 0); // We prefill the buffer of lengthBuffer 0

            // In the first byte we store the type and the methods
            buffer[DEFINITON_BYTE] = (method << 6) + type; // Since type and enum are enums having less than 15 members each we can simply use bitshft to store it in 1 byte;
            buffer[1] = '\n';
            return buffer;
        };

        BaseObj deserialize(const BPC::Buffer &buffer) //decode Package
        {
            BaseObj obj = {
                .type_ = static_cast<BPC::BaseType>(buffer[DEFINITON_BYTE] & 0xF),
                .method_ = static_cast<BPC::Method>(buffer[DEFINITON_BYTE] >> 4)
            };
            std::string qtype[] = { "REQUEST", "RESPONSE", "OTHER" };
            std::string qmethods[] = { "CREATE", "JOIN" };

            for (int i = 0; i != 3; i++) {
                if (obj.method_ == i)
                    std::cout << "Method:" << std::string(qmethods[i]) << std::endl;
                if (obj.type_ == i)
                    std::cout << "Req:" << std::string(qtype[i]) << std::endl;
            }
            return obj;
        };

      private:
        CommunicationManager();

      private:
        static CommunicationManager instance_;
    };
};

#endif /* BPC_HPP_ */

