/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** JoinHandler
*/

#include "JoinHandler.hpp"

#include "Protocol.hpp"
#include "Server.hpp"
#include "engine/core/components/PositionComponent.hpp"
#include "handlers/UDP/SpawnHandler/SpawnHandler.hpp"
#include "nlohmann/json.hpp"
#include "scene_loader/SceneLoader.hpp"
#include "types.hpp"

namespace rtype::server {
    JoinHandler::JoinHandler(Lobby &owner)
        : AHandlerUDP(owner)
    { }

    void JoinHandler::receiveRequest(const Network::UdpPackage &package)
    {
        static const std::string playerTemplate = "{\"base\":\"Player\"}";
        static const nlohmann::json json(playerTemplate);

        if (this->owner_.isFull()) {
            this->refusePlayer(package);
            return;
        }
        auto player = JsonLoader::createEntity(this->owner_.scene->getEntityManager(), json);
        if (!player) {
            this->refusePlayer(package);
            return;
        }
        unsigned idx = 0;
        entity_id_t id = player->getId();
        const char *buffer = reinterpret_cast<const char *>(&id);
        BPC::Buffer body(8 + playerTemplate.size());

        for (; idx < sizeof(id); ++idx) {
            body[idx] = buffer[idx];
        }
        for (const auto &it : playerTemplate) {
            body[idx] = playerTemplate[idx];
            ++idx;
        }
        auto &handler = this->owner_.handlers[BPC::SPAWN];
        for (const auto &it : this->owner_.players) {
            handler->sendRequest(it.endpoint, &body);
        }
        this->newPlayer(package, player);
    }

    void JoinHandler::receiveResponse(const Network::UdpPackage &package)
    { }

    BPC::Method JoinHandler::getMethod() const
    {
        return BPC::JOIN;
    }

    void JoinHandler::refusePlayer(const Network::UdpPackage &package) const
    {
        Network::UdpPackage response(package, BPC::RESPONSE);
        unsigned id = -1;
        char *buffer = (char *)&id;

        response.body.resize(24);
        for (unsigned i = 0; i < sizeof(id); ++i) {
            response.body[i] = buffer[i];
        }
        this->sendResponse(response);
    }

    void JoinHandler::newPlayer(const Network::UdpPackage &package, const std::shared_ptr<Entity> &player) const
    {
        Network::UdpPackage response(package, BPC::RESPONSE);
        JoinHandler::ServerResponseBody body;
        auto pos = player->getComponent<PositionComponent>();
        auto ref = this->owner_.players.emplace_back();

        ref.id = player->getId();
        ref.endpoint = package.endpoint;
        body.playerID = ref.id;
        body.x = pos->x;
        body.y = pos->y;
        response.body.resize(24 + this->owner_.map.size());
        char *buffer = reinterpret_cast<char *>(&body);
        unsigned i = 0;
        for (; i < 24; ++i) {
            response.body[i] = buffer[i];
        }
        for (unsigned idx = 0; idx < this->owner_.map.size(); ++idx) {
            response.body[i] = this->owner_.map[idx];
        }
        this->sendResponse(response);
    }
}
