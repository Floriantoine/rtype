/*
** EPITECH PROJECT, 2020
** server
** File description:
** Server
*/

#include "Server.hpp"

#include "Protocol.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/write.hpp>
#include <functional>
#include <iostream>
#include <pstl/glue_algorithm_defs.h>

#define BPC_CM (rtype::BPC::CommunicationManager::Get())

namespace rtype::Network {
    TcpSession::TcpSession(tcp::socket &&socket)
        : socket_(std::move(socket))
    {
        std::cout << "Session begin..." << std::endl;
    }

    void TcpSession::start(msg_handler &&on_msg, err_handler &&on_err)
    {
        this->on_message_ = on_msg;
        this->on_error_ = on_err;

        this->async_read();
    }

    void TcpSession::async_read()
    {
        auto self = shared_from_this();
        boost::asio::async_read_until(this->socket_, this->streambuf_, '\n',
            [self](err_code err, std::size_t nbytes) {
                if (err == boost::asio::error::eof || err == boost::asio::error::connection_refused || err == boost::asio::error::connection_aborted) {
                    std::cerr << "Client: " << self->socket_.remote_endpoint() << " disconnected." << std::endl;
                    self->socket_.close();
                    self->on_error_();
                } else
                    self->on_read(err, nbytes);
            });
    }

    void TcpSession::async_write()
    {
        auto self = shared_from_this();
        auto tmp = this->outgoing_.front();

        boost::asio::async_write(this->socket_, boost::asio::buffer(tmp),
            [self](err_code err, std::size_t nbytes) {
                if (!err)
                    self->on_write(err, nbytes);
                else
                    self->on_error_();
            });
    }

    tcp::socket &TcpSession::getSocket()
    {
        return this->socket_;
    }

    void TcpSession::on_read(err_code err, std::size_t nbytes)
    {
        std::stringstream msg;

        std::cout << "Reading something..." << std::endl;
        if (!err) {
            msg << std::istream(&this->streambuf_).rdbuf();
            this->streambuf_.consume(nbytes);

            auto str = msg.str();
            std::cout << str << std::endl;
            BPC::Buffer buffer(str.begin(), str.end());
            std::cout << "Received: " << buffer.size() << " bytes from client" << std::endl;
            BPC_CM.Deserialize(buffer);
            rtype::BPC::Package package = {
                rtype::BPC::BaseType::REQUEST,
                rtype::BPC::Method::CREATE,
                42,
                { "localhost", 4219 },
            };

            buffer = BPC_CM.Serialize(package);
            this->outgoing_.push(buffer);
            this->async_write();
        } else {
            std::cerr << "Reading failed: " << err.message() << std::endl;
            this->socket_.close();
            this->on_error_();
        }
    }

    void TcpSession::on_write(err_code err, std::size_t nbytes)
    {
        std::cerr << "Sending.." << std::endl;
        if (!err) {
            this->outgoing_.pop();
            if (!this->outgoing_.empty())
                this->async_write();
        } else {
            this->socket_.close();
            this->on_error_();
        }
    }

    TcpServer::TcpServer(boost::asio::io_context &io_context, std::uint16_t port)
        : io_context_(io_context)
        , acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
    {
        std::cout << "TCP Server" << std::endl;
        this->accept_handler();
    }

    void TcpServer::accept_handler()
    {
        this->socket_.emplace(this->io_context_);
        this->acceptor_.async_accept(*this->socket_, [&](err_code err) {
            if (!err) {
                auto client = std::make_shared<TcpSession>(std::move(*this->socket_));
                std::cout << client->getSocket().remote_endpoint(err) << " s'est connecté au server" << std::endl;
                std::cout << "We have a new commer" << std::endl;
                this->clients_.insert(client);
                client->start([&, client](const BPC::Buffer &buffer) {},
                    [&, client] {
                        std::erase_if(this->clients_, [&](const std::shared_ptr<TcpSession> &session) {
                            return (!session->getSocket().is_open());
                        });
                        for (auto it = this->clients_.begin(); it != this->clients_.end(); it++) {
                            auto &sock = it->get()->getSocket();
                            std::cout << "Client: " << sock.remote_endpoint() << " still alive." << std::endl;
                        }
                    });
                this->accept_handler();
            } else
                std::cerr << "Error Accept: " + err.message() << std::endl;
        });
    }

    //void TcpServer::receive_handler(const BPC::Buffer &buffer)
    //{
    //std::cout << "RECEIVE PACKAGE:" << std::endl;
    //}

    UdpServer::UdpServer(boost::asio::io_context &io_context)
        : io_context_(io_context)
    {
        std::cout << "UDP Server" << std::endl;
        this->socket_.emplace(io_context_, udp::endpoint(udp::v4(), 0));
        std::cout << "endpoint: " << this->socket_->local_endpoint() << std::endl;
    }

    void UdpServer::read(std::function<void(const BPC::Package &)> onRead)
    {
        std::stringstream msg;
        auto mutableBuffer = this->streambuf_.prepare(4096);
        this->socket_->async_receive_from(mutableBuffer, this->remote_endpoint_,
            [&](err_code err, std::size_t nbytes) {
                if (!err) {
                    std::cout << "Received " << nbytes << " bytes" << std::endl;
                    this->streambuf_.commit(nbytes);
                    std::istream is(&this->streambuf_);
                    std::string str;
                    is >> str;
                    std::cout << str << std::endl;
                    BPC::Buffer buffer(str.begin(), str.end());
                    onRead(BPC_CM.Deserialize(buffer));
                    read(onRead);
                    rtype::BPC::Package package = {
                        rtype::BPC::BaseType::REQUEST,
                        rtype::BPC::Method::CREATE,
                        42,
                        { "localhost", 4219 },
                    };

                    auto buf = BPC_CM.Serialize(package);
                    write(buf);
                } else
                    std::cerr << "Error Somewhere" << err.message() << std::endl;
            });
    }

    void UdpServer::write(const BPC::Buffer &buffer)
    {
        this->socket_->async_send_to(boost::asio::buffer(buffer), this->remote_endpoint_,
            [&](err_code err, std::size_t nsize) {
                if (err) {
                    std::cerr << "Write: " + err.message() << std::endl;
                }
            });
    }
}
