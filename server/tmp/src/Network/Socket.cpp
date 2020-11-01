/*
** EPITECH PROJECT, 2020
** server
** File description:
** Socket
*/

#include "Socket.hpp"

Network::Socket::Socket(int port)
    : port_(port)
{
    std::cout << "Instantiate Socket" << std::endl;
}

Network::Socket::~Socket()
{
    std::cout << "Destruct Socket" << std::endl;
}

void Network::Socket::start()
{
    io_context_.run();
}

Network::TcpSession::TcpSession(tcp::socket &&socket)
    : socket_(std::move(socket))
{
}

void Network::TcpSession::read()
{
    boost::asio::async_read_until(this.socket_, this.streambuf_, '\n', [self = shared_from_this()](err_code error, std::size_t nbytes)
    {
        self->on_read(error, nbytes);
    });
}

void Network::TcpSession::write()
{
    std::string tmp = this.outgoing_msgs_.front();

    boost::asio::async_write(this.socket_, boost::asio::const_buffer(tmp.c_str(), tmp.size()), [self = shared_from_this()] (err_code error, std::size_t nbytes)
    {
        self->on_write(error, nbytes);
    });
}

void Network::TcpSession::on_read(err_code err, std::size_t nbytes)
{
    std::cout << "enter on_read" << std::endl;
    if (!err) {
        std::cout << "no error" << std::endl;
        std::stringstream msg;

        msg << std::istream(&this->streambuf_).rdbuf();
        this->streambuf_.consume(nbytes);

        std::string str = msg.str();
        bsip::Buffer buffer(str.begin(), str.end());

        this->_on_message(package);
    } else {
        std::cout << "error" << std::endl;
        this->socket_.close();
        this->on_error();
    }
}

void Network::TcpSession::on_write(err_code err, std::size_t nbytes)
{
    if (!err) {
        this->outgoing_msgs_.pop();
        if (!this->outgoing_msgs_.empty())
            async_write();
    } else {
        this->socket_.close();
        this->on_error(err);
    }
}

//Network::TcpServer::TcpServer(int port)
    //: Socket(port), acceptor_(io_context_, tcp::endpoint(tcp::v4(), port))
//{
    //std::cout << "Instantiate TCP Socket" << std::endl;
//}

//Network::TcpServer::~TcpServer() noexcept
//{
    //std::cout << "Destruct TCP Socket" << std::endl;
//}
