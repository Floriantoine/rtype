/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** DestroyHandler
*/

#include "DestroyHandler.hpp"

#include "Protocol.hpp"

namespace rtype::client {
    DestroyHandler::DestroyHandler(GameClient &owner)
        : AHandlerUDP(owner)
    { }

    void DestroyHandler::receiveRequest(const BPC::Package &package)
    { }

    void DestroyHandler::receiveResponse(const BPC::Package &package)
    { }

    BPC::Method DestroyHandler::getMethod() const
    {
        return BPC::DESTROY;
    }
}
