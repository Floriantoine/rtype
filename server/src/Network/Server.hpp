/*
** EPITECH PROJECT, 2020
** server
** File description:
** Server
*/

#pragma once

#include "Protocol.hpp"
#include "boost/asio/ip/tcp.hpp"
#include "boost/asio/ip/udp.hpp"
#include "boost/asio/streambuf.hpp"

#include <functional>
#include <iostream>
#include <queue>
#include <unordered_set>

using boost::asio::ip::tcp;
using boost::asio::ip::udp;
using err_code = boost::system::error_code;

namespace rtype::server::Network {
    class TcpSession : public std::enable_shared_from_this<TcpSession> {
      public:
        using err_handler = std::function<void()>;
        using msg_handler = std::function<void(const rtype::BPC::Package &, TcpSession &)>;

        TcpSession(tcp::socket &&socket, const msg_handler &on_message, const err_handler &on_error);
        ~TcpSession() noexcept = default;
        TcpSession(const TcpSession &) = delete;
        TcpSession(TcpSession &&) = delete;
        TcpSession &operator=(const TcpSession &) = delete;
        TcpSession &operator=(TcpSession &&) = delete;

        tcp::socket &getSocket();

        void start();
        void async_read();
        void async_write(const BPC::Package &package, const std::shared_ptr<std::function<void()>> &onSent = nullptr);

      private:
        tcp::socket socket_;
        BPC::Buffer streambuf_;
        const msg_handler &on_message_;
        const err_handler &on_error_;

        bool isErrorAndHandle(const err_code &err, bool isError);
    };

    class TcpServer {
      public:
        TcpServer(boost::asio::io_context &io_context, std::uint16_t port, const TcpSession::msg_handler &onRead);
        ~TcpServer() noexcept = default;
        TcpServer(const TcpServer &) = delete;
        TcpServer(TcpServer &&) = delete;
        TcpServer operator=(const TcpServer &) = delete;
        TcpServer operator=(TcpServer &&) = delete;

      private:
        void receive_handler(const rtype::BPC::Buffer &buffer);
        void accept_handler(const TcpSession::msg_handler &onRead);
        void disconnect_handler();

      private:
        tcp::acceptor acceptor_;
        boost::asio::io_context &io_context_;
        std::optional<tcp::socket> socket_;
        std::unordered_set<std::shared_ptr<TcpSession>> clients_;
        const TcpSession::err_handler on_error_;
    };

    struct UdpPackage : public BPC::Package {
        udp::endpoint endpoint;

        UdpPackage() = default;
        UdpPackage(const UdpPackage &other, BPC::BaseType type);
        UdpPackage(const UdpPackage &other);
        UdpPackage &operator=(const UdpPackage &other);
    };

    class UdpServer {
      public:
        using msg_handler = std::function<void(const UdpPackage &)>;

        UdpServer(const msg_handler &onRead);
        ~UdpServer() = default;
        UdpServer(const UdpServer &) = delete;
        UdpServer(UdpServer &&) = delete;
        UdpServer &operator=(const UdpServer &);
        UdpServer &operator=(UdpServer &&) = delete;

        void start();
        void poll();
        unsigned short getPort() const;
        err_code write(const UdpPackage &package);

      private:
        boost::asio::io_context io_context_;
        udp::endpoint remote_endpoint_;
        std::optional<udp::socket> socket_;
        BPC::Buffer streambuf_;
        const msg_handler &on_message_;
    };
}
