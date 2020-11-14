/*
** EPITECH PROJECT, 2020
** server
** File description:
** Server
*/

#pragma once

#include "Protocol.hpp"

#include <boost/asio.hpp>
#include <iostream>
#include <queue>
#include <unordered_set>

using boost::asio::ip::tcp;
using boost::asio::ip::udp;
using err_code = boost::system::error_code;

using msg_handler = std::function<void(const rtype::BPC::Buffer &)>;
using err_handler = std::function<void()>;

namespace rtype::Network {
    class TcpSession : public std::enable_shared_from_this<TcpSession> {
      public:
        TcpSession(tcp::socket &&socket);
        ~TcpSession() noexcept = default;
        TcpSession(const TcpSession &) = delete;
        TcpSession(TcpSession &&) = delete;
        TcpSession &operator=(const TcpSession &) = delete;
        TcpSession &operator=(TcpSession &&) = delete;

        tcp::socket &getSocket();

        void start(msg_handler &&on_msg, err_handler &&on_err);
        void async_read();

      private:
        void async_write();
        void on_read(err_code err, std::size_t nbytes);
        void on_write(err_code err, std::size_t nbytes);

      private:
        tcp::socket socket_;
        boost::asio::streambuf streambuf_;
        std::queue<rtype::BPC::Buffer> outgoing_;
        msg_handler on_message_;
        err_handler on_error_;
    };
    class TcpServer {
      public:
        TcpServer(boost::asio::io_context &io_context, std::uint16_t port);
        ~TcpServer() noexcept = default;
        TcpServer(const TcpServer &) = delete;
        TcpServer(TcpServer &&) = delete;
        TcpServer operator=(const TcpServer &) = delete;
        TcpServer operator=(TcpServer &&) = delete;

      private:
        void receive_handler(const rtype::BPC::Buffer &buffer);
        void accept_handler();

      private:
        tcp::acceptor acceptor_;
        boost::asio::io_context &io_context_;
        std::optional<tcp::socket> socket_;
        std::unordered_set<std::shared_ptr<TcpSession>> clients_;
    };

    class UdpServer {
      public:
        UdpServer(boost::asio::io_context &io_context);
        ~UdpServer() = default;
        UdpServer(const UdpServer &) = delete;
        UdpServer(UdpServer &&) = delete;
        UdpServer &operator=(const UdpServer &);
        UdpServer &operator=(UdpServer &&) = delete;

        void read();
        boost::asio::io_context &io_context_;
      private:
        void write(const rtype::BPC::Buffer &buffer);
        udp::endpoint remote_endpoint_;
        std::optional<udp::socket> socket_;
        boost::asio::streambuf streambuf_;
    };
}
