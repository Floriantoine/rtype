/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** GameStateHandler
*/

#include "GameStateHandler.hpp"

namespace rtype::server {
    GameStateHandler::GameStateHandler(std::vector<Player> &players)
        : AHandlerUDP(players)
    {
    }

    void GameStateHandler::response(const BPC::Package &package)
    {
    }

    void GameStateHandler::request(const BPC::Package &package)
    {
    }
}
