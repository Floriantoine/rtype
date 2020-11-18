/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** ShootHandler
*/

#include "ShootHandler.hpp"

#include "Protocol.hpp"
#include "engine/core/components/BehaviourComponent.hpp"
#include "engine/core/components/PositionComponent.hpp"
#include "engine/core/ecs/entity/Entity.hpp"
#include "game/behaviours/PlayerBehaviour.hpp"

#include <memory>

namespace rtype::client {
    ShootHandler::ShootHandler(GameClient &owner)
        : AHandlerUDP(owner)
    { }

    void ShootHandler::receiveRequest(const BPC::Package &package)
    { }

    void ShootHandler::receiveResponse(const BPC::Package &package)
    { }

    BPC::Method ShootHandler::getMethod() const
    {
        return BPC::SHOOT;
    }
}
