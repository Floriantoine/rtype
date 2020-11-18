/*
** EPITECH PROJECT, 2020
** client
** File description:
** Client
*/

#include "Client.hpp"
#include "Exception.hpp"
#include "Protocol.hpp"

#include <cstdint>

namespace rtype::client::Network {
    TcpClient::TcpClient(asio::io_context &io_context, const std::string_view &address, std::uint16_t port)
        : io_context_(io_context)
        , serv_socket_(io_context)
        , endpoint_(asio::ip::make_address(address), port)
    {
        std::cout << "Start Tcp Client" << std::endl;
        this->on_error_ = [&] {
            throw rtype::client::Exception("TCP client: " + this->error_code_.message());
        };
        this->start();
    }

    void TcpClient::start()
    {
        this->serv_socket_.connect(this->endpoint_, this->error_code_);
        if (this->error_code_)
            this->on_error_();
    }

    void TcpClient::send(const BPC::Package &package)
    {
        this->serv_socket_.write_some(asio::buffer(BPC::Serialize(package)), this->error_code_);
        if (this->error_code_)
            this->on_error_();
    }

    rtype::BPC::Package TcpClient::recv()
    {
        // Read the header
        this->recbuf_.resize(HEADER_SIZE);
        auto nbytes = this->serv_socket_.read_some(asio::buffer(this->recbuf_), this->error_code_);
        auto package = BPC::Deserialize(this->recbuf_);

        if (HEADER_SIZE != nbytes || this->error_code_)
            this->on_error_();
        package.body.resize(package.bodySize);
        nbytes = this->serv_socket_.read_some(asio::buffer(package.body), this->error_code_);
        if (package.bodySize != nbytes || this->error_code_)
            this->on_error_();
        return package;
    };

    UdpClient::UdpClient(const msg_handler &onMessage)
        : resolver_(this->io_context_)
        , on_message_ { onMessage }
    {
    }

    void UdpClient::connect(const std::string_view &address, std::uint16_t port)
    {
        this->socket_.emplace(this->io_context_, udp::endpoint(udp::v4(), 0));
        this->serv_endpoints_ = *this->resolver_.resolve(udp::v4(), address, std::to_string(port));
    }

    void UdpClient::poll()
    {
        this->io_context_.poll();
    }

    void UdpClient::start()
    {
        auto self = this->shared_from_this();

        this->socket_->async_receive_from(
            boost::asio::buffer(this->streambuf_), this->serv_endpoints_,
            [self](err_code err, std::size_t nbytes) {
                if (nbytes == HEADER_SIZE  && !err) {
                    BPC::Package pkg = BPC::Deserialize(self->streambuf_);
                    pkg.body.reserve(pkg.bodySize);
                    nbytes = self->socket_->receive_from(boost::asio::buffer(pkg.body), self->serv_endpoints_, asio::socket_base::message_flags(), err);
                    if (nbytes == pkg.bodySize && !err) {
                        self->on_message_(pkg, *self);
                        self->streambuf_.resize(HEADER_SIZE, 0);
                        self->start();
                    }
                }
            });
    }

    void UdpClient::send(const BPC::Package &package)
    {
        socket_->send_to(asio::buffer(BPC::Serialize(package)), this->serv_endpoints_);
    }
}
