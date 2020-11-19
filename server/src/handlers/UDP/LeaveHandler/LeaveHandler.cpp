/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** LeaveHandler
*/

#include "LeaveHandler.hpp"

#include "Protocol.hpp"

namespace rtype::server {
    LeaveHandler::LeaveHandler(Lobby &owner)
        : AHandlerUDP(owner)
    { }

    void LeaveHandler::receiveRequest(const Network::UdpPackage &package)
    {
        this->sendResponse(package);
        this->owner_.removePlayer(package.endpoint);
    }

    void LeaveHandler::receiveResponse(const Network::UdpPackage &package)
    { }

    BPC::Method LeaveHandler::getMethod() const
    {
        return BPC::LEAVE;
    }
}
