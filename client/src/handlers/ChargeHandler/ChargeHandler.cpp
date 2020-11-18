/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** ChargeHandler
*/

#include "ChargeHandler.hpp"

namespace rtype::client {
    ChargeHandler::ChargeHandler(GameClient &owner)
        : AHandlerUDP(owner)
    { }

    void ChargeHandler::receiveRequest(const BPC::Package &package)
    {
        // TODO
    }

    void ChargeHandler::receiveResponse(const BPC::Package &package)
    { }

    BPC::Method ChargeHandler::getMethod() const
    {
        return BPC::CHARGE;
    }
}
