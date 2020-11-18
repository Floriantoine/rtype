/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** PositionHandler
*/

#include "PositionHandler.hpp"

#include "Protocol.hpp"

namespace rtype::client {
    PositionHandler::PositionHandler(GameClient &owner)
        : AHandlerUDP(owner)
    {
    }

    void PositionHandler::receiveRequest(const BPC::Package &package)
    { }

    void PositionHandler::receiveResponse(const BPC::Package &package)
    { }

    BPC::Method PositionHandler::getMethod() const
    {
        return BPC::POSITION;
    }
}
