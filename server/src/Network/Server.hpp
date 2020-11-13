/*
** EPITECH PROJECT, 2020
** server
** File description:
** Server
*/

#include <stdio.h>

#ifndef SERVER_HPP_
    #define SERVER_HPP_

    #include "BinaryProtocolCommunication.hpp"

    #include <boost/asio.hpp>
    #include <boost/asio/io_context.hpp>
    #include <cstdint>
    #include <iostream>
    #include <memory.h>
    #include <memory>
    #include <optional>
    #include <queue>
    #include <unordered_set>

namespace BPC = BinaryProtocolCommunication;

using boost::asio::ip::tcp;
using boost::asio::ip::udp;
using err_code = boost::system::error_code;

using msg_handler = std::function<void(const BPC::Buffer &)>;
using err_handler = std::function<void()>;

namespace rtype::Network {
    template <typename T>
    // TODO: typesafety with static_assert
    class IOServer {
      public:
        IOServer(boost::asio::io_context &io_context, std::uint16_t port)
            : io_context_(io_context)
            , Server_(io_context, port)
        {
            std::cout << "Start IOServer" << std::endl;
        };
        ~IOServer<T>() noexcept = default;
        IOServer<T>(const IOServer &) = delete;
        IOServer &operator=(const IOServer<T> &) = delete;
        IOServer &operator=(IOServer<T> &&) = delete;

        void start()
        {
            this->io_context_.run();
        };
        void end() {};
        void write() {};
        void read() {};

      private:
        T Server_;
        boost::asio::io_context &io_context_;
    };

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
        std::queue<BPC::Buffer> outgoing_;
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
        void receive_handler(const BPC::Buffer &buffer);
        void accept_handler();

      private:
        tcp::acceptor acceptor_;
        boost::asio::io_context &io_context_;
        std::optional<tcp::socket> socket_;
        std::unordered_set<std::shared_ptr<TcpSession>> clients_;
    };

    class UdpServer {
      public:
        UdpServer(boost::asio::io_context &io_context, std::uint16_t port);
        ~UdpServer() = default;
        UdpServer(const UdpServer &) = delete;
        UdpServer(UdpServer &&) = delete;
        UdpServer &operator=(const UdpServer &) = delete;
        UdpServer &operator=(UdpServer &&) = delete;

        void read();

      private:
        void write(const BPC::Buffer &buffer);
        boost::asio::io_context &io_context_;
        udp::endpoint remote_endpoint_;
        std::optional<udp::socket> socket_;
        boost::asio::streambuf streambuf_;
    };
}
#endif /* SERVER_HPP_ */
