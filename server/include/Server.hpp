/*
** EPITECH PROJECT, 2020
** server
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <boost/asio.hpp>
#include <iostream>
#include <optional>
#include <queue>
#include <unordered_set>
#include <memory.h>
#include <cstdint>
#include "BinaryProtocolCommunication.hpp"
#include "IServer.hpp"

namespace BPC = BinaryProtocolCommunication;

using boost::asio::ip::tcp;
using boost::asio::ip::udp;
using err_code = boost::system::error_code;

using msg_handler = std::function<void (const BPC::Buffer &)>;
using err_handler = std::function<void ()>;

namespace rtype {
    namespace Network  {
        template <typename T>
        // TODO: typesafety with static_assert
        class IOServer : public IServer {
        public:
          IOServer<T>(boost::asio::io_context &io_context, std::uint16_t port);
          ~IOServer<T>() noexcept = default;
          IOServer<T>(const IOServer &) = default;
          IOServer<T> &operator=(const IOServer<T> &) = default;
          IOServer<T> &operator=(IOServer<T> &&) = default;

          void start(){};
          void end(){};
          void write(){};
          void read(){};

        private:
          T Server_;
        };

        class TcpSession : public std::enable_shared_from_this<TcpSession> {
            public: TcpSession(tcp::socket &&socket);
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

                void accept_handler();
                void receive_handler(const BPC::Buffer &buffer);
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

                void read(void);
                void write(void);

            private:
                boost::asio::io_context &io_context_;
                udp::endpoint sender_endpoint_;
                std::optional<udp::socket> socket_;
        };
    };
}
#endif /* SERVER_HPP_ */

