/*
** EPITECH PROJECT, 2020
** client
** File description:
** Client
*/

#pragma once

#include "BinaryProtocolCommunication.hpp"

#include <boost/asio.hpp>
#include <iostream>
#include <vector>

namespace rtype::Network {
    namespace asio = boost::asio;

    typedef asio::ip::tcp tcp;
    typedef asio::ip::udp udp;

    template <class T>
    class IOClient {
      public:
        IOClient(asio::io_context &io_context, const std::string_view &adress, std::uint16_t port)
            : client_(io_context, adress, port)
            , io_context_(io_context) {};

        ~IOClient() = default;
        IOClient(const IOClient &) = delete;
        IOClient(IOClient &&) = delete;
        IOClient &operator=(const IOClient &) = delete;
        IOClient &operator=(IOClient &&) = delete;

        rtype::BPC::Buffer &read()
        {
            return this->client_.recv(buffer_);
        };
        void write(rtype::BPC::Buffer buffer)
        {
            this->client_.send(buffer);
        };

      private:
        T client_;
        asio::io_context &io_context_;
        std::vector<unsigned char> buffer_;
    };

    class TcpClient {
      public:
        TcpClient(asio::io_context &io_context, const std::string_view &adress, std::uint16_t port);
        ~TcpClient() noexcept = default;
        TcpClient(const TcpClient &) = delete;
        TcpClient(TcpClient &&) = delete;
        TcpClient &operator=(const TcpClient &) = delete;
        TcpClient &operator=(TcpClient &&) = delete;

        void start();
        void send(const rtype::BPC::Buffer &buffer);
        rtype::BPC::Buffer &recv(std::vector<unsigned char> &);

      private:
        asio::io_context &io_context_;
        tcp::socket serv_socket_;
        tcp::endpoint endpoint_;
    };

    class UdpClient {
      public:
        UdpClient(asio::io_context &io_context, const std::string_view &adress, std::uint16_t port);
        ~UdpClient() noexcept = default;
        UdpClient(const UdpClient &) = delete;
        UdpClient(UdpClient &&) = delete;
        UdpClient &operator=(const UdpClient &) = delete;
        UdpClient &operator=(UdpClient &&) = delete;

        void start();
        void send(const rtype::BPC::Buffer &buffer);
        rtype::BPC::Buffer &recv(std::vector<unsigned char> &);

      private:
        asio::io_context &io_context_;
        udp::socket socket_;
        udp::endpoint serv_endpoints;
        udp::resolver resolver_;
    };
};
