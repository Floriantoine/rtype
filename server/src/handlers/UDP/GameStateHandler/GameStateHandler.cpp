/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** GameStateHandler
*/

#include "GameStateHandler.hpp"
#include "Protocol.hpp"
#include "game/ABehaviour.hpp"
#include "engine/core/components/BehaviourComponent.hpp"
#include "types.hpp"

namespace rtype::server {
    GameStateHandler::GameStateHandler(Lobby &owner)
        : AHandlerUDP(owner)
    { }

    void GameStateHandler::receiveRequest(const Network::UdpPackage &package)
    {
        auto *body = package.getBodyTo<GameStateHandler::ClientRequestBody>();

        if (*this->owner_.state == GameState::RUN || body->state != GameState::RUN)
            return;

        this->owner_.scene->getComponentManager().apply<BehaviourComponent>([&](BehaviourComponent *holder) {
            auto behaviour = holder->getBehaviour<ABehaviour>();
            if (behaviour) {
                behaviour->setLobby(this->owner_.shared_from_this());
            }
        });

        this->owner_.state = GameState::RUN;
        this->sendResponse(package);

        ServerRequestBody req;
        req.state = GameState::RUN;
        for (const auto &it : this->owner_.players) {
            if (it.endpoint == package.endpoint)
                continue;
            this->sendRequest(it.endpoint, &req);
        }
    }

    void GameStateHandler::receiveResponse(const Network::UdpPackage &package)
    { }
    
    BPC::Method GameStateHandler::getMethod() const
    {
        return BPC::GAME_STATE;
    }
}
