/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** DropHandler
*/

#include "DropHandler.hpp"
#include "Protocol.hpp"

namespace rtype::server {
    DropHandler::DropHandler(Lobby &owner)
        : AHandlerUDP(owner)
    { }

    void DropHandler::receiveRequest(const Network::UdpPackage &package)
    {
        // TODO
    }

    void DropHandler::receiveResponse(const Network::UdpPackage &package)
    { }

    BPC::Method DropHandler::getMethod() const
    {
        return BPC::DROP;
    }
}
