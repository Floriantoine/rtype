/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** HitHandler
*/

#include "HitHandler.hpp"

#include "Protocol.hpp"

namespace rtype::server {
    HitHandler::HitHandler(Lobby &owner)
        : AHandlerUDP(owner)
    {
    }

    void HitHandler::receiveRequest(const Network::UdpPackage &package)
    {
    }

    void HitHandler::receiveResponse(const Network::UdpPackage &package)
    {
    }

    BPC::Method HitHandler::getMethod() const
    {
        return BPC::HIT;
    }
}
