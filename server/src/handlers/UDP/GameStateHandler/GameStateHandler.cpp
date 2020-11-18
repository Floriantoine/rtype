/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** GameStateHandler
*/

#include "GameStateHandler.hpp"
#include "Protocol.hpp"
#include "types.hpp"

namespace rtype::server {
    GameStateHandler::GameStateHandler(Lobby &owner)
        : AHandlerUDP(owner)
    { }

    void GameStateHandler::receiveRequest(const Network::UdpPackage &package)
    {
        auto *body = package.getBodyTo<GameStateHandler::ClientRequestBody>();

        if (body->state != GameState::RUN)
            return;
        this->owner_.state_ = GameState::RUN;
        this->sendResponse(package);

        ServerRequestBody req;
        req.state = GameState::RUN;
        for (const auto &it : this->owner_.players_) {
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
