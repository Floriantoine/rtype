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

namespace rtype::server {
    ShootHandler::ShootHandler(Lobby &owner)
        : AHandlerUDP(owner)
    { }

    void ShootHandler::receiveRequest(const Network::UdpPackage &package)
    {
        auto *body = package.getBodyTo<ClientRequestBody>();
        auto behaviour = this->owner_.getEntityComponent<BehaviourComponent>(body->playerID);
        auto playerBehaviour = behaviour->getBehaviour<PlayerBehaviour>();
        std::shared_ptr<Entity> missile = nullptr;

        if (playerBehaviour) {
            missile = playerBehaviour->shoot();
        }
        ServerResponseBody response{};
        response.missileID = 0;
        response.confirmation = false;

        if (!missile) {
            this->sendResponse(package, &response);
            return;
        }
        response.missileID = missile->getId();
        response.confirmation = true;
        this->sendResponse(package, &response);

        auto *pos = missile->getComponent<PositionComponent>();
        std::string json = R"({"base":"PlayerMissile","components":[{"type":"position","x":)";
        json += pos->x;
        json += ",\"y\":";
        json += pos->y;
        json += "}]}";

        BPC::Buffer responseBody(json.size() + 8);
        char *idPtr = reinterpret_cast<char *>(&response.missileID);
        unsigned idx = 0;
        for (; idx < sizeof(response.missileID); ++idx) {
            responseBody[idx] = idPtr[idx];
        }
        for (const auto &it : json) {
            responseBody[idx] = it;
            ++idx;
        }
        auto &handler = this->owner_.handlers[BPC::SPAWN];
        for (const auto &it : this->owner_.players) {
            if (it.endpoint == package.endpoint)
                continue;
            handler->sendRequest(it.endpoint, &responseBody);
        }
    }

    void ShootHandler::receiveResponse(const Network::UdpPackage &package)
    { }

    BPC::Method ShootHandler::getMethod() const
    {
        return BPC::SHOOT;
    }
}
