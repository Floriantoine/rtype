/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** JoinHandler
*/

#include "JoinHandler.hpp"

#include "Protocol.hpp"

namespace rtype::server {
    JoinHandler::JoinHandler(Lobby &owner)
        : AHandlerUDP(owner)
    {
    }

    void JoinHandler::receiveRequest(const Network::UdpPackage &package)
    {
    }

    void JoinHandler::receiveResponse(const Network::UdpPackage &package)
    {
    }

    BPC::Method JoinHandler::getMethod() const
    {
        return BPC::JOIN;
    }
}
