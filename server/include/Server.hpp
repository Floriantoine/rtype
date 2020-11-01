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
#include <memory>
#include <optional>
#include <unordered_set>

/*
 * for uid generation
 */

#include <boost/uuid/uuid_generators.hpp>

using boost::asio::ip::tcp;
using err_code = boost::system::error_code;

namespace Network  {
    class UdpSocket {
        public:
            UdpSocket() { std::cout << "Udp Socket" << std::endl; };
            ~UdpSocket() = default;
    };

    class TcpSocket {
        public:
            TcpSocket(tcp::socket &&socket) : socket_(std::move(socket))
            { std::cout << "Tcp Socket" << std::endl; };
            ~TcpSocket() = default;

            void read() { this->on_read(); };
        private:
            on_read();
            tcp::socket socket_;
            uuid id_;
    };

    template<typename TSocket>
        class Server {
            public:
                Server(int port) { std::cout << "Server" << std::endl; };
                ~Server() = default;
                Server(const Server &) = delete;
                Server(const Server &&) = delete;
                Server operator=(const Server &) = delete;
                Server operator=(const Server &&) = delete;

                void start() { std::cout << "Tcp Socket" << std::endl; };
            private:
                boost::asio::io_context io_context;
        };

    template<>
        class Server<TcpSocket> {
            public:
                Server(int port) : acceptor_(io_context_, tcp::endpoint(tcp::v4(), port))
                { std::cout << "Udp Server" << std::endl; };
                ~Server() = default;
                Server(const Server &) = delete;
                Server(const Server &&) = delete;
                Server operator=(const Server &) = delete;
                Server operator=(const Server &&) = delete;

            private:
                void accept_handler() {
                    this->acceptor_.async_accept(
                            [this](err_code err, this->socket_)
                            {
                                std::make_shared<TcpSocket>(std::move(this->socket_))->start();
                            });
                };

            private:
                tcp::acceptor acceptor_;
                std::optional<tcp::socket> socket_;
                boost::asio::io_context io_context_;
                std::unordered_set<std::shared_ptr<TcpSocket>>
        };
};

#endif /* SERVER_HPP_ */

