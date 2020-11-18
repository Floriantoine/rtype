/*
** EPITECH PROJECT, 2020
** server
** File description:
** Server
*/

#include "Server.hpp"

#include "Protocol.hpp"
#include "boost/asio/buffer.hpp"
#include "boost/asio/socket_base.hpp"
#include "boost/asio/write.hpp"

#include <functional>
#include <iostream>
#include <memory>
#include <pstl/glue_algorithm_defs.h>

namespace rtype::server::Network {
    TcpSession::TcpSession(tcp::socket &&socket, const msg_handler &on_message, const err_handler &on_error)
        : socket_ { std::move(socket) }
        , on_message_ { on_message }
        , on_error_ { on_error }
    {
        std::cout << "Session begin..." << std::endl;
    }

    void TcpSession::start()
    {
        this->async_read();
    }

    void TcpSession::async_read()
    {
        auto self = shared_from_this();

        this->streambuf_.resize(HEADER_SIZE, 0);
        this->socket_.async_read_some(boost::asio::buffer(self->streambuf_),
            [self](err_code err, std::size_t nbytes) {
                if (!self->isErrorAndHandle(err, nbytes != HEADER_SIZE)) {
                    BPC::Package pkg = BPC::Deserialize(self->streambuf_);
                    pkg.body.reserve(pkg.bodySize);
                    nbytes = self->socket_.read_some(boost::asio::buffer(pkg.body), err);
                    if (!self->isErrorAndHandle(err, nbytes != pkg.bodySize)) {
                        self->on_message_(pkg, *self);
                        self->async_read();
                    }
                }
            });
    }

    void TcpSession::async_write(const BPC::Package &package, std::shared_ptr<std::function<void()>> onSent)
    {
        auto self = shared_from_this();

        auto buffer = BPC::Serialize(package);
        boost::asio::async_write(this->socket_, boost::asio::buffer(buffer),
            [&self, onSent](err_code err, std::size_t nbytes) {
                if (err)
                    self->on_error_();
                else if (onSent.get() != nullptr) {
                    (*onSent)();
                }
            });
    }

    bool TcpSession::isErrorAndHandle(const err_code &err, bool isError)
    {
        if (err == boost::asio::error::eof || err == boost::asio::error::connection_refused || err == boost::asio::error::connection_aborted) {
            std::cerr << "Client: " << this->socket_.remote_endpoint() << " disconnected." << std::endl;
            this->socket_.close();
            this->on_error_();
            return true;
        } else if (isError || err) {
            this->on_error_();
            return true;
        }
        return false;
    }

    tcp::socket &TcpSession::getSocket()
    {
        return this->socket_;
    }

    TcpServer::TcpServer(boost::asio::io_context &io_context, std::uint16_t port, const TcpSession::msg_handler &onRead)
        : io_context_(io_context)
        , acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
        , on_error_ { [&] {
            this->disconnect_handler();
        } }
    {
        std::cout << "TCP Server" << std::endl;
        this->accept_handler(onRead);
    }

    void TcpServer::accept_handler(const TcpSession::msg_handler &onRead)
    {
        this->socket_.emplace(this->io_context_);
        this->acceptor_.async_accept(*this->socket_, [&](err_code err) {
            if (!err) {
                auto client = std::make_shared<TcpSession>(std::move(*this->socket_), onRead, this->on_error_);
                std::cout << client->getSocket().remote_endpoint(err) << " s'est connecté au server" << std::endl;
                std::cout << "We have a new commer" << std::endl;
                this->clients_.insert(client);
                client->start();
                this->accept_handler(onRead);
            } else {
                std::cerr << "Error Accept: " + err.message() << std::endl;
            }
        });
    }

    void TcpServer::disconnect_handler()
    {
        std::erase_if(this->clients_, [&](const std::shared_ptr<TcpSession> &session) {
            return (!session->getSocket().is_open());
        });
        for (auto it = this->clients_.begin(); it != this->clients_.end(); it++) {
            auto &sock = it->get()->getSocket();
            std::cout << "Client: " << sock.remote_endpoint() << " still alive." << std::endl;
        }
    }

    UdpPackage::UdpPackage(const UdpPackage &other, BPC::BaseType type)
        : BPC::Package(other, type)
        , endpoint(other.endpoint)
    { }

    UdpPackage::UdpPackage(const UdpPackage &other)
        : BPC::Package(other)
        , endpoint(other.endpoint)
    { }

    UdpPackage &UdpPackage::operator=(const UdpPackage &other)
    {
        BPC::Package::operator=(other);
        this->endpoint = other.endpoint;
        return *this;
    }

    UdpServer::UdpServer(const msg_handler &onRead)
        : on_message_(onRead)
    {
        std::cout << "UDP Server" << std::endl;
        this->socket_.emplace(io_context_, udp::endpoint(udp::v4(), 0));
        std::cout << "endpoint: " << this->socket_->local_endpoint() << std::endl;
    }

    void UdpServer::start()
    {
        this->streambuf_.resize(HEADER_SIZE, 0);
        this->socket_->async_receive_from(boost::asio::buffer(this->streambuf_), this->remote_endpoint_,
            [&](err_code err, std::size_t nbytes) {
                if (!err && nbytes == HEADER_SIZE) {
                    UdpPackage package;
                    BPC::Deserialize(package, this->streambuf_);
                    package.endpoint = this->remote_endpoint_;
                    package.body.resize(package.bodySize);
                    nbytes = this->socket_->receive_from(boost::asio::buffer(package.body), this->remote_endpoint_, boost::asio::socket_base::message_flags(), err);
                    if (!err && nbytes == HEADER_SIZE) {
                        this->on_message_(package);
                        this->start();
                    }
                }
            });
    }

    void UdpServer::poll()
    {
        this->io_context_.poll();
    }

    err_code UdpServer::write(const UdpPackage &package)
    {
        BPC::Buffer buffer = BPC::Serialize(package);
        err_code err;
        this->socket_->send_to(boost::asio::buffer(buffer), package.endpoint, boost::asio::socket_base::message_flags(), err);
        return err;
    }

    unsigned short UdpServer::getPort() const
    {
        return this->socket_->local_endpoint().port();
    }
}
