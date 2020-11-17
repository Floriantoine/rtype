/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** MoveHandler
*/

#include "MoveHandler.hpp"
#include "Protocol.hpp"

namespace rtype::server {
    MoveHandler::MoveHandler(Lobby &owner)
        : AHandlerUDP(owner)
    {
    }

    void MoveHandler::receiveRequest(const Network::UdpPackage &package)
    {
        AHandlerUDP::receiveRequest(package);
    }

    void MoveHandler::receiveResponse(const Network::UdpPackage &package)
    {
        AHandlerUDP::receiveResponse(package);
    }
    
    BPC::Method MoveHandler::getMethod() const
    {
        return BPC::MOVE;
    }
}
