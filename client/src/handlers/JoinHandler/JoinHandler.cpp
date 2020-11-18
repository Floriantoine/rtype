/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** JoinHandler
*/

#include "JoinHandler.hpp"

#include "Protocol.hpp"
#include "engine/core/components/PositionComponent.hpp"
#include "handlers/SpawnHandler/SpawnHandler.hpp"
#include "nlohmann/json.hpp"
#include "scene_loader/SceneLoader.hpp"
#include "types.hpp"

namespace rtype::client {
    JoinHandler::JoinHandler(GameClient &owner)
        : AHandlerUDP(owner)
    { }

    void JoinHandler::receiveRequest(const BPC::Package &package)
    { }

    void JoinHandler::receiveResponse(const BPC::Package &package)
    { }

    BPC::Method JoinHandler::getMethod() const
    {
        return BPC::JOIN;
    }

    void JoinHandler::refusePlayer(const BPC::Package &package) const
    {
    }

    void JoinHandler::newPlayer(const BPC::Package &package, const std::shared_ptr<Entity> &player) const
    {
    }
}
