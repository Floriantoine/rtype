/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Client main file
*/

#include "Client.hpp"
#include "Protocol.hpp"

#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/write.hpp>
#include <iostream>
#include <sstream>

int main()
{
    auto cm = rtype::BPC::CommunicationManager::Get();
    boost::asio::io_context io_context;

    rtype::Network::IOClient<rtype::Network::UdpClient> client(io_context, "127.0.0.1", 4219);

    rtype::BPC::Package package = {
        rtype::BPC::BaseType::REQUEST,
        rtype::BPC::Method::CREATE,
        42,
        {"localhost", 4219},
    };

    auto buffer = cm.Serialize(package);
    client.write(buffer);
    auto rec = client.read();
    cm.Deserialize(buffer);

    return 0;
}
