/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Client main file
*/

#include "Client.hpp"
#include "Protocol.hpp"

#include <iostream>
#include <sstream>

int main(int ac, char *av[])
{
    boost::asio::io_context io_context;

    //std::uint16_t i = std::stoi(av[1]);
    rtype::Network::IOClient<rtype::Network::TcpClient> client(io_context, "127.0.0.1", 4000);

    rtype::BPC::Package package;
    package.type = rtype::BPC::BaseType::REQUEST;
    package.method = rtype::BPC::Method::CREATE;
    package.timestamp = 42;

    auto buffer = rtype::BPC::Serialize(package);
    client.write(buffer);
    auto rec = client.read();
    rtype::BPC::Deserialize(buffer);

    return 0;
}
