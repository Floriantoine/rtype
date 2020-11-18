/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** DestroyHandler
*/

#include "DestroyHandler.hpp"

#include "Protocol.hpp"

namespace rtype::server {
    DestroyHandler::DestroyHandler(Lobby &owner)
        : AHandlerUDP(owner)
    { }

    void DestroyHandler::receiveRequest(const Network::UdpPackage &package)
    { }

    void DestroyHandler::receiveResponse(const Network::UdpPackage &package)
    { }

    BPC::Method DestroyHandler::getMethod() const
    {
        return BPC::DESTROY;
    }
}
