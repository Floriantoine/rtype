/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Behaviour abstract class
*/

#include "ABehaviour.hpp"

#include "Protocol.hpp"
#include "handlers/UDP/DestroyHandler/DestroyHandler.hpp"
#include "handlers/UDP/PositionHandler/PositionHandler.hpp"

namespace rtype::server {
    void ABehaviour::setLobby(const std::shared_ptr<Lobby> &lobby)
    {
        this->lobby_ = lobby;
    }
    
    void ABehaviour::sendPosition(const PositionComponent *position)
    {
        auto &handler = this->lobby_->handlers[BPC::POSITION];
        PositionHandler::ServerRequestBody body{};
        body.entityID = this->getEntity()->getId();
        body.x = position->x;
        body.y = position->y;

        this->sendRequestToPlayers(BPC::POSITION, &body, 0, false);
    }

    void ABehaviour::onDestroy()
    {
        DestroyHandler::ServerRequestBody body{};
        body.entityID = this->getEntity()->getId();

        this->sendRequestToPlayers(BPC::DESTROY, &body);
    }
}
