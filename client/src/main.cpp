/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Client main file
*/

#include "BinaryProtocolCommunication.hpp"

#include "Client.hpp"

#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/write.hpp>
#include <iostream>
#include <sstream>

namespace io = boost::asio;
namespace ip = io::ip;
using tcp = io::ip::tcp;
using error_code = boost::system::error_code;

int main()
{
    auto cm = BPC::CommunicationManager::Get();
    io::io_context io_context;

    rtype::Network::IOClient<rtype::Network::UdpClient> client(io_context, "127.0.0.1", 4219);

    auto buffer = cm.serialize(BPC::BaseType::REQUEST, BPC::Method::CREATE);
    client.write(buffer);
    auto rec = client.read();
    cm.deserialize(rec);
    return 0;
}
