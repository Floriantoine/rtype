/*
** EPITECH PROJECT, 2020
** client
** File description:
** Client
*/

#include "Client.hpp"


rtype::Network::TcpClient::TcpClient(boost::asio::io_context &io_context, const std::string_view &adress, std::uint16_t port)
    : io_context_(io_context), serv_socket_(io_context), endpoint_(boost::asio::ip::make_address(adress), port)
{
    std::cout << "Start Tcp Client" << std::endl;
    try {
        this->start();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

void rtype::Network::TcpClient::start()
{
    this->serv_socket_.connect(this->endpoint_);
}

void rtype::Network::TcpClient::send(const BPC::Buffer &buffer)
{
    this->serv_socket_.write_some(boost::asio::buffer(buffer));
}

// TODO: change the corpse... see With Albert
std::size_t parse_header(const boost::asio::streambuf &)
{
    return 42;
}

BPC::Buffer &rtype::Network::TcpClient::recv(std::vector<unsigned char> &recbuf)
{
    // Read the header
    int header_size = 42; // TODO: This should be a macro
    recbuf.resize(header_size);

    auto bytes = this->serv_socket_.read_some(boost::asio::buffer(recbuf));
    std::cout << "READ: " << bytes << " bytes from socket" << std::endl;

    // Extract the size of the body
    //auto body_size = parse_header(recbuf);
    //recbuf.resize(body_size);
    //boost::asio::read(this->serv_socket_, boost::asio::buffer(recbuf));
    return recbuf;
};

rtype::Network::UdpClient::UdpClient(boost::asio::io_context &io_context, const std::string_view &adress, std::uint16_t port)
    : io_context_(io_context), resolver_(io_context), socket_(io_context, udp::endpoint(udp::v4(), 0))
{
    std::cout << "Start Udp Client" << std::endl;
    this->serv_endpoints = *this->resolver_.resolve(udp::v4(), adress, std::to_string(port));
}

void rtype::Network::UdpClient::send(const BPC::Buffer &buffer)
{ 
    socket_.send_to(boost::asio::buffer(buffer), this->serv_endpoints);
}

BPC::Buffer &rtype::Network::UdpClient::recv(std::vector<unsigned char> &recbuf)
{
    // Read the header
    int header_size = 8;
    recbuf.resize(header_size);

    this->socket_.receive_from(boost::asio::buffer(recbuf), this->serv_endpoints);

    // Extract the size of the body
    return recbuf;
};
