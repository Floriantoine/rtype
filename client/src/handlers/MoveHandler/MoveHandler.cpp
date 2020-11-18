/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** MoveHandler
*/

#include "MoveHandler.hpp"

#include "Protocol.hpp"
#include "engine/core/components/BehaviourComponent.hpp"
#include "game/behaviours/PlayerBehaviour.hpp"

namespace rtype::client {
    MoveHandler::MoveHandler(GameClient &owner)
        : AHandlerUDP(owner)
    { }

    void MoveHandler::receiveRequest(const BPC::Package &package)
    { }

    void MoveHandler::receiveResponse(const BPC::Package &package)
    { }

    BPC::Method MoveHandler::getMethod() const
    {
        return BPC::MOVE;
    }
}
