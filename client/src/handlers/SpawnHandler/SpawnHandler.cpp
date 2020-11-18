/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** SpawnHandler
*/

#include "SpawnHandler.hpp"

namespace rtype::client {
    SpawnHandler::SpawnHandler(GameClient &owner)
        : AHandlerUDP(owner)
    { }

    void SpawnHandler::receiveRequest(const BPC::Package &package)
    { }

    void SpawnHandler::receiveResponse(const BPC::Package &package)
    { }

    BPC::Method SpawnHandler::getMethod() const
    {
        return BPC::SPAWN;
    }
}
