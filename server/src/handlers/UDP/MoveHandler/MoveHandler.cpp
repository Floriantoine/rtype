/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** MoveHandler
*/

#include "MoveHandler.hpp"

namespace rtype::server {
    MoveHandler::MoveHandler(std::vector<Player> &players)
        : AHandlerUDP(players)
    {
    }

    void MoveHandler::response(const BPC::Package &package)
    {
    }

    void MoveHandler::request(const BPC::Package &package)
    {
    }
}
