/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** LeaveHandler
*/

#include "LeaveHandler.hpp"

#include "Protocol.hpp"

namespace rtype::client {
    LeaveHandler::LeaveHandler(GameClient &owner)
        : AHandlerUDP(owner)
    { }

    void LeaveHandler::receiveRequest(const BPC::Package &package)
    { }

    void LeaveHandler::receiveResponse(const BPC::Package &package)
    { }

    BPC::Method LeaveHandler::getMethod() const
    {
        return BPC::LEAVE;
    }
}
