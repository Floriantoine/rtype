/*
** EPITECH PROJECT, 2020
** client
** File description:
** Client
*/

#pragma once

#include "Protocol.hpp"
#include "boost/asio.hpp"
#include "boost/asio/io_context.hpp"
#include "boost/system/error_code.hpp"

#include <iostream>
#include <memory>
#include <optional>
#include <system_error>
#include <vector>

using err_handler = std::function<void()>;
using err_code = boost::system::error_code;

namespace rtype::client::Network {
    namespace asio = boost::asio;

    typedef asio::ip::tcp tcp;
    typedef asio::ip::udp udp;

    class TcpClient {
      public:
        TcpClient(asio::io_context &io_context, const std::string_view &address, std::uint16_t port);
        ~TcpClient() noexcept = default;
        TcpClient(const TcpClient &) = delete;
        TcpClient(TcpClient &&) = delete;
        TcpClient &operator=(const TcpClient &) = delete;
        TcpClient &operator=(TcpClient &&) = delete;

        err_code send(const BPC::Package &package);
        rtype::BPC::Package recv();

      private:
        rtype::BPC::Buffer recbuf_;
        boost::system::error_code error_code_;
        asio::io_context &io_context_;
        tcp::socket serv_socket_;
        tcp::endpoint endpoint_;
        err_handler on_error_;

        void start();
    };

    class UdpClient : public std::enable_shared_from_this<UdpClient> {
      public:
        using msg_handler = std::function<void(const BPC::Package &, const UdpClient &)>;

        UdpClient(const msg_handler &onMessage);
        ~UdpClient() noexcept = default;
        UdpClient(const UdpClient &) = delete;
        UdpClient(UdpClient &&) = delete;
        UdpClient &operator=(const UdpClient &) = delete;
        UdpClient &operator=(UdpClient &&) = delete;

        void connect(const std::string_view &address, std::uint16_t port);
        void poll();
        void start();
        err_code send(const BPC::Package &package);

      private:
        BPC::Buffer streambuf_;
        boost::asio::io_context io_context_;
        std::optional<udp::socket> socket_ { std::nullopt };
        udp::endpoint serv_endpoints_;
        udp::resolver resolver_;
        const msg_handler &on_message_;
    };
};
