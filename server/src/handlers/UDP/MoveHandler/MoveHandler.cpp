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

namespace rtype::server {
    MoveHandler::MoveHandler(Lobby &owner)
        : AHandlerUDP(owner)
    { }

    void MoveHandler::receiveRequest(const Network::UdpPackage &package)
    {
        auto *requestBody = package.getBodyTo<ClientRequestBody>();
        auto *behaviourComponent = this->owner_.getEntityComponent_<BehaviourComponent>(requestBody->playerID);

        if (behaviourComponent == nullptr)
            return;
        auto behaviour = behaviourComponent->getBehaviour<PlayerBehaviour>();
        switch (requestBody->direction) {
            case Direction::UP:
                behaviour->isUpKeyPressed_ = requestBody->state;
                break;
            case Direction::DOWN:
                behaviour->isDownKeyPressed_ = requestBody->state;
                break;
            case Direction::LEFT:
                behaviour->isLeftKeyPressed_ = requestBody->state;
                break;
            default:
                behaviour->isRightKeyPressed_ = requestBody->state;
                break;
        }
        this->sendResponse(package);
        for (const auto &it : this->owner_.players_) {
            if (it.endpoint == package.endpoint)
                continue;
            this->sendRequest(it.endpoint, &requestBody);
        }
    }

    void MoveHandler::receiveResponse(const Network::UdpPackage &package)
    { }

    BPC::Method MoveHandler::getMethod() const
    {
        return BPC::MOVE;
    }
}
