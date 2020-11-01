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

#include <iostream>
#include <string>
#include <string_view>
#include <queue>
#include <vector>
#include <boost/algorithm/string.hpp>

namespace BinaryProtocolComunication
{
    using Buffer = std::vector<unsigned char>; // binary to send
    namespace BPC = BinaryProtocolComunication;

    enum BaseType {
        REQUEST,
        RESPONSE,
        OTHER
    };

    enum Method {
        CREATE,
        JOIN,
    };

    struct BaseObj {
        BaseType type_;
        Method method_;
    };

    class CommunicationManager { // singleton
    public:
      ~CommunicationManager() noexcept = default;
      static CommunicationManager Get() { return instance_; };

      void bonjour() { std::cout << "Bonjour" << std::endl; };

    //   size_t getTotalSizeArgs(std::vector<std::string> args)
    //   {
    //         size_t size = 0;

    //         for (const auto &arg: args) {
    //             size += arg.size() + 1;
    //         }
    //         return size;
    //   };

    //   void encodePeerInfos(BPC::Buffer &buffer, const std::string &ip_adress,
    //                        const std::string &port) {
    //     auto d_port = std::stoi(port);
    //     std::vector<std::string> str_vec_ip;
    //     boost::split(str_vec_ip, ip_adress, boost::is_any_of("."));
    //     int count = PEER_INFO;

    //     for (const auto &str : str_vec_ip) {
    //         std::cout << "str: " + str << std::endl;
    //         buffer[count] = static_cast<unsigned char>(std::atoi(str.c_str()));
    //         std::cout << "Buffer[" << count << "]:" + str << std::endl;
    //         count += 1;
    //     }
    //     // we encode the port on 16 bits therefore 2 bytes
    //     buffer[count] = (d_port & 0xFF00) >> 8;
    //     buffer[count + 1] = (d_port & 0xFF);
    //   };

      BPC::Buffer serialize(BPC::BaseType type, BPC::Method method) //encode Package
      {
            size_t lengthBuffer = ARG_START;
            BPC::Buffer buffer(lengthBuffer, 0); // We prefill the buffer of lengthBuffer 0
  
            // In the first byte we store the type and the methods
            buffer[DEFINITON_BYTE] = (method << 4) + type; // Since type and enum are enums having less than 15 members each we can simply use bitshft to store it in 1 byte;
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

            for (int i = 0 ; i != 3; i++) {
                if (obj.method_ == i)
                    std::cout << "Req:" << std::string(qmethods[i]) << std::endl;
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

