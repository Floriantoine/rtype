/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** GrabHandler
*/

#include "GrabHandler.hpp"

#include "Protocol.hpp"

namespace rtype::client {
    GrabHandler::GrabHandler(GameClient &owner)
        : AHandlerUDP(owner)
    { }

    void GrabHandler::receiveRequest(const BPC::Package &package)
    { }

    void GrabHandler::receiveResponse(const BPC::Package &package)
    { }
    
    BPC::Method GrabHandler::getMethod() const
    {
        return BPC::GRAB;
    }
}
