/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** AHandlerTCP
*/

#include "AHandlerTCP.hpp"

#include "GameServer.hpp"

#include <iostream>
#include <string>

namespace rtype::server {
    AHandlerTCP::AHandlerTCP(GameServer &owner)
        : owner_(owner)
    { }

    void AHandlerTCP::unknowPacket(const BPC::Package &package, Network::TcpSession &client)
    {
        std::string ip = client.getSocket().local_endpoint().address().to_string();
        auto port = client.getSocket().local_endpoint().port();

        std::cerr << "Received a malformed packed from: " << ip << ":" << port << std::endl;
    }

    void AHandlerTCP::receive(const BPC::Package &package, Network::TcpSession &client)
    {
        if (package.type == BPC::BaseType::REQUEST) {
            this->receiveRequest(package, client);
        } else if (package.type == BPC::BaseType::RESPONSE) {
            this->receiveRequest(package, client);
        } else {
            AHandlerTCP::unknowPacket(package, client);
        }
    }
}
