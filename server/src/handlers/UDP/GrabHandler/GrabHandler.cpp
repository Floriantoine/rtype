/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** GrabHandler
*/

#include "GrabHandler.hpp"

#include "Protocol.hpp"

namespace rtype::server {
    GrabHandler::GrabHandler(Lobby &owner)
        : AHandlerUDP(owner)
    {
    }

    void GrabHandler::receiveRequest(const Network::UdpPackage &package)
    {
        AHandlerUDP::receiveRequest(package);
    }

    void GrabHandler::receiveResponse(const Network::UdpPackage &package)
    {
        AHandlerUDP::receiveResponse(package);
    }
    
    BPC::Method GrabHandler::getMethod() const
    {
        return BPC::GRAB;
    }
}
