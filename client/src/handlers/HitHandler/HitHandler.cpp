/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** HitHandler
*/

#include "HitHandler.hpp"

#include "Protocol.hpp"

namespace rtype::client {
    HitHandler::HitHandler(GameClient &owner)
        : AHandlerUDP(owner)
    { }

    void HitHandler::receiveRequest(const BPC::Package &package)
    { }

    void HitHandler::receiveResponse(const BPC::Package &package)
    { }

    BPC::Method HitHandler::getMethod() const
    {
        return BPC::HIT;
    }
}
