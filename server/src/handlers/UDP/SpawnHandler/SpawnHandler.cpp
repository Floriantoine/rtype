/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** SpawnHandler
*/

#include "SpawnHandler.hpp"

#include "Protocol.hpp"

namespace rtype::server {
    SpawnHandler::SpawnHandler(Lobby &owner)
        : AHandlerUDP(owner)
    { }

    void SpawnHandler::receiveRequest(const Network::UdpPackage &package)
    { }

    void SpawnHandler::receiveResponse(const Network::UdpPackage &package)
    { }

    BPC::Method SpawnHandler::getMethod() const
    {
        return BPC::SPAWN;
    }
}
