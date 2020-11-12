/*
** EPITECH PROJECT, 2020
** server
** File description:
** Server
*/

#include "Server.hpp"

#include "BinaryProtocolCommunication.hpp"

#include <boost/asio/buffer.hpp>
#include <boost/asio/write.hpp>
#include <functional>

auto g_cm = BPC::CommunicationManager::Get();

rtype::Network::TcpSession::TcpSession(tcp::socket &&socket)
    : socket_(std::move(socket))
{
    std::cout << "Session begin..." << std::endl;
}

void rtype::Network::TcpSession::start(msg_handler &&on_msg, err_handler &&on_err)
{
    this->on_message_ = on_msg;
    this->on_error_ = on_err;

    this->async_read();
}

void rtype::Network::TcpSession::async_read()
{
    auto self = shared_from_this();
    boost::asio::async_read_until(this->socket_, this->streambuf_, '\n',
        [self](err_code err, std::size_t nbytes) {
            self->on_read(err, nbytes);
        });
}

void rtype::Network::TcpSession::async_write()
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

tcp::socket &rtype::Network::TcpSession::getSocket()
{
    return this->socket_;
}

void rtype::Network::TcpSession::on_read(err_code err, std::size_t nbytes)
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
        g_cm.deserialize(buffer);
        buffer = g_cm.serialize(BPC::RESPONSE, BPC::CREATE);
        this->outgoing_.push(buffer);
        this->async_write();
    } else {
        std::cerr << "Reading failed: " << err.message() << std::endl;
        this->socket_.close();
        this->on_error_();
    }
}

void rtype::Network::TcpSession::on_write(err_code err, std::size_t nbytes)
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

rtype::Network::TcpServer::TcpServer(boost::asio::io_context &io_context, std::uint16_t port)
    : io_context_(io_context)
    , acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
{
    std::cout << "TCP Server" << std::endl;
    this->accept_handler();
}

void rtype::Network::TcpServer::accept_handler()
{
    this->socket_.emplace(this->io_context_);
    this->acceptor_.async_accept(*this->socket_, [&](err_code err) {
        if (!err) {
            auto client = std::make_shared<rtype::Network::TcpSession>(std::move(*this->socket_));
            std::cout << client->getSocket().remote_endpoint(err) << " s'est connecté au server" << std::endl;
            std::cout << "We have a new commer" << std::endl;
            this->clients_.insert(client);
            client->start(std::bind(&rtype::Network::TcpServer::receive_handler, this, std::placeholders::_1),
                [&, client] {
                    if (this->clients_.erase(client))
                        std::cout << "We have one less" << std::endl;
                });
            this->accept_handler();
        } else
            std::cerr << "Error Accept: " + err.message() << std::endl;
    });
}

void rtype::Network::TcpServer::receive_handler(const BPC::Buffer &buffer)
{
    std::cout << "RECEIVE PACKAGE:" << std::endl;
}

rtype::Network::UdpServer::UdpServer(boost::asio::io_context &io_context, std::uint16_t port)
    : io_context_(io_context)
{
    std::cout << "UDP Server" << std::endl;
    this->socket_.emplace(io_context_, udp::endpoint(udp::v4(), port));
    this->read();
}

void rtype::Network::UdpServer::read(void)
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
                g_cm.deserialize(buffer);
                // HERE to resend to server
                // -------------------------
                auto buf = g_cm.serialize(BPC::RESPONSE, BPC::CREATE);
                write(buf);
                // -------------------------
                read();
            }
                else
                     std::cerr << "Error SOmewhere" << err.message() << std::endl;
            });
}

void rtype::Network::UdpServer::write(const BPC::Buffer &buffer)
{
    this->socket_->async_send_to(boost::asio::buffer(buffer), this->remote_endpoint_, 
            [&](err_code err, std::size_t nsize) {
                if (err) 
                    std::cerr << "Write: " + err.message() << std::endl;
            });
}
