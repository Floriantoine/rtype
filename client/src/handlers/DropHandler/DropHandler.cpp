/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** DropHandler
*/

#include "DropHandler.hpp"
#include "Protocol.hpp"

namespace rtype::client {
    DropHandler::DropHandler(GameClient &owner)
        : AHandlerUDP(owner)
    { }

    void DropHandler::receiveRequest(const BPC::Package &package)
    {
        // TODO
    }

    void DropHandler::receiveResponse(const BPC::Package &package)
    { }

    BPC::Method DropHandler::getMethod() const
    {
        return BPC::DROP;
    }
}
