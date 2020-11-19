/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** CreateHandler
*/

#include "CreateHandler.hpp"

#include "GameServer.hpp"
#include "engine/core/systems/BehaviourSystem.hpp"
#include "handlers/AHandlerTCP.hpp"
#include "scene_loader/SceneLoader.hpp"
#include "types.hpp"

#include <cstring>
#include <iostream>
#include <memory>
#include <new>

namespace rtype::server {
    CreateHandler::ClientRequestBody::ClientRequestBody(const std::vector<unsigned char> &buffer)
        : mapName(buffer.size() + 1, '\0')
    {
        const auto len = buffer.size();

        for (auto i = 0UL; i < len; ++i) {
            this->mapName[i] = buffer[i];
        }
    }

    CreateHandler::CreateHandler(GameServer &owner)
        : AHandlerTCP(owner)
    { }

    void CreateHandler::initScene(Scene &scene)
    {
        scene.createSystem<BehaviourSystem>();
    }

    void CreateHandler::receiveResponse(const BPC::Package &package, Network::TcpSession &client)
    {
    }

    void CreateHandler::receiveRequest(const BPC::Package &requestPackage, Network::TcpSession &client)
    {
        const ClientRequestBody requestBody(requestPackage.body);
        ServerResponseBody responseBody;
        BPC::Package responsePackage(requestPackage, BPC::RESPONSE);
        std::shared_ptr<std::function<void()>> onSent = nullptr;

        try {
            std::string scenePath = this->owner_.config_.scenesDir + requestBody.mapName + ".json";
            SceneManager sceneManager;
            auto scenePtr = JsonLoader::createScene(sceneManager, scenePath);
            CreateHandler::initScene(*scenePtr);
            const Lobby &lobby = this->owner_.dispatcher_->createLobby(std::move(scenePtr), requestBody.mapName);

            responseBody.port = lobby.getPort();
            memcpy(&responseBody.lobbyID, lobby.id.data(), sizeof(lobby_id_t));
            responsePackage.setBodyFrom(&responseBody);
            onSent = std::make_shared<std::function<void()>>([&client] {
                client.getSocket().close();
            });
        } catch (const std::bad_alloc &_) {
        }
        client.async_write(responsePackage, onSent);
    }
}
