/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** PositionHandler
*/

#include "PositionHandler.hpp"

#include "Protocol.hpp"
#include "handlers/AHandlerUDP.hpp"

namespace rtype::server {
    PositionHandler::PositionHandler(Lobby &owner)
        : AHandlerUDP(owner)
    {
    }

    void PositionHandler::receiveRequest(const Network::UdpPackage &package)
    { }

    void PositionHandler::receiveResponse(const Network::UdpPackage &package)
    { }

    BPC::Method PositionHandler::getMethod() const
    {
        return BPC::POSITION;
    }
}
