/*
** EPITECH PROJECT, 2020
** server
** File description:
** Socket
*/

#ifndef SOCKET_HPP_
#define SOCKET_HPP_

#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <optional>
#include <unordered_set>
#include <queue>

#include "ISocket.hpp"

using boost::asio::ip::tcp;
using boost::asio::ip::udp;
using err_code = boost::system::error_code;

namespace Network {
    class Socket : public ISocket
    {
        public:
            Socket(int port);
            ~Socket();
            Socket(const Socket &) = delete;
            Socket(Socket &&) = delete;
            Socket &operator=(const Socket &) = delete;
            Socket &operator=(Socket &&) = delete;

            void start();
            void read();
            //void end();
            //void listen();
            //void connect();
        protected:
            boost::asio::io_context io_context_;
        private:
            int socket_;
            int port_;
    };

    class TcpSession : public std::enable_shared_from_this<TcpSession>
    {
        public:
            TcpSession(tcp::socket &&socket);
            ~TcpSession() = default;
            TcpSession(const TcpSession &) = delete;
            TcpSession(TcpSession &&) = delete;
            TcpSession &operator=(const TcpSession &) = delete;
            TcpSession &operator=(TcpSession &&) = delete;

            void read();
            void write();
            void on_read(err_code err, std::size_t nbytes);
            void on_write(err_code err, std::size_t nbytes);
            void on_error(err_code err, std::size_t nbytes);
        private:
            tcp::socket socket_;
            boost::asio::streambuf streambuf_;
            std::queue<std::string> outgoing_msgs_;
    };

    class TcpServer
    {
        public:
            TcpServer(int port);
            ~TcpServer() noexcept;
            TcpServer(const TcpServer &) = delete;
            TcpServer(TcpServer &&) = delete;
            TcpServer &operator=(const TcpServer &) = delete;
            TcpServer &operator=(TcpServer &&) = delete;

            void accept_handler();
        private:
            tcp::acceptor acceptor_;
            std::optional<tcp::socket> _socket;
            std::unordered_set<std::shared_ptr<TcpSession>> _clients;
    };

    //class UdpSocket : public Socket {
        //public:
            //UdpSocket(int port, serv_type type);
            //~UdpSocket() noexcept;
            //UdpSocket(const UdpSocket &) = delete;
            //UdpSocket(UdpSocket &&) = delete;
            //UdpSocket &operator=(const UdpSocket &) = delete;
            //UdpSocket &operator=(UdpSocket &&) = delete;
    //};

};
#endif /* SOCKET_HPP_ */
