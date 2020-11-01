/*
** EPITECH PROJECT, 2020
** server
** File description: 
** TCP Server member functions definition 
*/

#include <iostream>
#include <algorithm>
#include <memory>
#include "Server.hpp"
#include "User.hpp"
#include "BSIP.hpp"
#include "BSIPType.hpp"

BabelServer::TCPConnexion::TCPConnexion(tcp::socket&& socket)
        : _socket(std::move(socket)), _sender(_socket.remote_endpoint().address().to_string(), _socket.remote_endpoint().port())
{
}

void BabelServer::TCPConnexion::start(msg_handler &&on_msg, err_handler &&on_err)
{
    this->_on_message = on_msg;
    this->_on_error = on_err;

    this->async_read();
}

void BabelServer::TCPConnexion::post(const bsip::Buffer &msg)
{
    auto p = bsip::bin::decode(msg);

    std::cout << "about to send a package:" << std::endl;
    std::cout << p << std::endl << std::endl;
    /*
     * clean tout ca, conversion useless: string => buffer => string
     */
    std::string str(msg.begin(), msg.end());
    str += '\n';

    bool idle = _outgoing.empty();
    _outgoing.push(str);

    if (idle)
        this->async_write();
}

void BabelServer::TCPConnexion::async_read()
{
    boost::asio::async_read_until(_socket, _streambuf, '\n', [self = shared_from_this()](err_code error, std::size_t nbytes)
    {
        self->on_read(error, nbytes);
    });
}

void BabelServer::TCPConnexion::async_write()
{
    std::string tmp = _outgoing.front();

    boost::asio::async_write(_socket, boost::asio::const_buffer(tmp.c_str(), tmp.size()), [self = shared_from_this()] (err_code error, std::size_t nbytes)
    {
        self->on_write(error, nbytes);
    });
}


void BabelServer::TCPConnexion::on_read(err_code err, std::size_t nbytes)
{
    std::cout << "enter on_read" << std::endl;
    if (!err) {
        std::cout << "no error" << std::endl;
        std::stringstream msg;

        msg << std::istream(&_streambuf).rdbuf();
        _streambuf.consume(nbytes);

        std::string str = msg.str();
        bsip::Buffer buffer(str.begin(), str.end());

        bsip::BSIPPackage package = bsip::bin::decode(buffer);
        package.setSender(this->_sender);

        this->_on_message(package);
    } else {
        std::cout << "error" << std::endl;
        _socket.close();
        _on_error();
    }
}

void BabelServer::TCPConnexion::on_write(err_code err, std::size_t nbytes)
{
    if (!err) {
        _outgoing.pop();
        if (!_outgoing.empty())
            async_write();
    } else {
        _socket.close();
        _on_error();
    }
}

tcp::socket &BabelServer::TCPConnexion::getSocket()
{
    return _socket;
}

const bsip::Sender &BabelServer::TCPConnexion::getSender() const
{
    return this->_sender;
}

BabelServer::TCPServer::TCPServer(boost::asio::io_context &io_context, bsip::BSIPInterpreter &interpreter)
    : _io_context(io_context), _acceptor(io_context, tcp::endpoint(tcp::v4(), 4219)), _interpreter(interpreter)
{
    std::cout << "Start TCP Server" << std::endl;
}

BabelServer::TCPServer::~TCPServer() noexcept
{
    std::cout << "End TCP Server" << std::endl;
}

void BabelServer::TCPServer::async_accept_handler()
{
    _socket.emplace(_io_context);
    _acceptor.async_accept(*_socket, [&](err_code error) {
        if (!error) {
            auto client = std::make_shared<BabelServer::TCPConnexion>(std::move(*_socket));
            std::cout <<  client->getSocket().remote_endpoint(error) << " s'est connecté au server" << std::endl;

            std::cout << "We have a new commer" << std::endl;
            _clients.insert(client);
            client->start(
                    std::bind(&TCPServer::handlePacket, this, std::placeholders::_1),
                    [&, client] {
                        if (_clients.erase(client)) {
                            this->_interpreter.removeRegisteredClient(client->getSender());
                            std::cout << "We are one less" << std::endl;
                        }
                    }
            );
            std::cerr << error.message() << std::endl;
            async_accept_handler();
        } else
            std::cerr << error.message() << std::endl;
    });
}

void BabelServer::TCPServer::handlePacket(const bsip::BSIPPackage &package)
{
    bsip::SendingQueue queue = this->_interpreter.interpretPackage(package);

    std::cout << "receive package:" << std::endl;
    std::cout << package << std::endl;

    std::cout << "SendingQueue size: " << queue.size() << std::endl << std::endl;
    for (const auto &item : queue) {
        for (const auto &client : this->_clients) {
            if (client->getSender() == item.first) {
                client->post(item.second);
                client->async_read();
                std::cout << "T UNE SALOPE" << std::endl;
            }
        }
    }
    std::cout << "Everything as been well sended" << std::endl << std::endl << std::endl;
}
