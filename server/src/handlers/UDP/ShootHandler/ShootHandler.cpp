/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** ShootHandler
*/

#include "ShootHandler.hpp"
#include "Protocol.hpp"

namespace rtype::server {
    ShootHandler::ShootHandler(Lobby &owner)
        : AHandlerUDP(owner)
    {
    }

    void ShootHandler::receiveRequest(const Network::UdpPackage &package)
    {
        AHandlerUDP::receiveRequest(package);
    }

    void ShootHandler::receiveResponse(const Network::UdpPackage &package)
    {
        AHandlerUDP::receiveResponse(package);
    }
    
    BPC::Method ShootHandler::getMethod() const
    {
        return BPC::SHOOT;
    }
}
