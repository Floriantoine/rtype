/*
** EPITECH PROJECT, 2020
** client
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <boost/asio.hpp>
#include <iostream>
#include <vector>

#include "BinaryProtocolCommunication.hpp"

using boost::asio::ip::tcp;
using boost::asio::ip::udp;
namespace BPC = BinaryProtocolCommunication;

namespace rtype::Network {
    template<class T>
    class IOClient {
        public:
            IOClient(boost::asio::io_context &io_context, const std::string_view &adress, std::uint16_t port)
                : Client_(io_context, adress, port), io_context_(io_context)
            { }
            ~IOClient() = default;
            IOClient(const IOClient &) = delete;
            IOClient(IOClient &&) = delete;
            IOClient &operator=(const IOClient &) = delete;
            IOClient &operator=(IOClient &&) = delete;

            BPC::Buffer &read() { return this->Client_.recv(buffer_); };
            void write(BPC::Buffer buffer){ this->Client_.send(buffer); };
            
        private:
            T Client_;
            boost::asio::io_context &io_context_;
            //boost::asio::streambuf streambuf_;
            std::vector<unsigned char> buffer_;
    };

    class TcpClient {
        public:
            TcpClient(boost::asio::io_context &io_context, const std::string_view &adress, std::uint16_t port);
            ~TcpClient() noexcept = default;
            TcpClient(const TcpClient &) = delete;
            TcpClient(TcpClient &&) = delete;
            TcpClient &operator=(const TcpClient &) = delete;
            TcpClient &operator=(TcpClient &&) = delete;

            void start();
            void send(const BPC::Buffer &buffer);
            BPC::Buffer &recv(std::vector<unsigned char> &);

        private:
            boost::asio::io_context &io_context_;
            tcp::socket serv_socket_;
            tcp::endpoint endpoint_;
    };

    class UdpClient {
        public:
            UdpClient(boost::asio::io_context &io_context, const std::string_view &adress, std::uint16_t port);
            ~UdpClient() noexcept = default;
            UdpClient(const UdpClient &) = delete;
            UdpClient(UdpClient &&) = delete;
            UdpClient &operator=(const UdpClient &) = delete;
            UdpClient &operator=(UdpClient &&) = delete;

            void start();
            void send(const BPC::Buffer &buffer);
            BPC::Buffer &recv(std::vector<unsigned char> &);

        private:
            boost::asio::io_context &io_context_;
            udp::socket socket_;
            udp::endpoint serv_endpoints;
            udp::resolver resolver_;
    };
};

#endif /* CLIENT_HPP_ */

