/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Client main file
*/

#include <boost/asio/buffer.hpp>
#include <boost/asio/write.hpp>
#include <iostream>
#include <boost/asio.hpp>
#include <sstream>
#include "BinaryProtocolCommunication.hpp"

namespace io = boost::asio;
namespace BPC = BinaryProtocolCommunication;
namespace ip = io::ip;
using tcp = io::ip::tcp;
using error_code = boost::system::error_code;

int main()
{
    auto cm = BPC::CommunicationManager::Get();
    io::io_context io_context;
    tcp::socket socket(io_context);
    ip::address address = ip::make_address("127.0.0.1");
    tcp::endpoint endpoint(address, 4219);
    auto buffer = cm.serialize(BPC::BaseType::REQUEST, BPC::Method::CREATE);
    std::array<char, 1080> abuffer;

    error_code error;
    socket.connect(endpoint, error);

    if(!error) {
        std::cout << "The connection has been established!";
    } else {
        std::cerr << "Something went wrong :(: " + error.message() << std::endl;
    }
    std::cout << "Writing " << socket.write_some(boost::asio::buffer(buffer)) << " datas to server" << std::endl;
    std::cout << "Reading " << socket.read_some(boost::asio::buffer(abuffer)) << " datas to server" << std::endl;
    //std::stringstream tmp;
    //tmp << std::istream(&abuffer).rdbuf();
    //abuffer.consume(1080);
    //auto str = tmp.str();
    BPC::Buffer bbuffer(abuffer.begin(), abuffer.end());
    cm.deserialize(bbuffer);

    

    while (true);
    return 0;
}
