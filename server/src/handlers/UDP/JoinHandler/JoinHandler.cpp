/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** JoinHandler
*/

#include "JoinHandler.hpp"

namespace rtype::server {
    JoinHandler::JoinHandler(std::vector<Player> &players)
        : AHandlerUDP(players)
    {
    }

    void JoinHandler::response(const BPC::Package &package)
    {
    }

    void JoinHandler::request(const BPC::Package &package)
    {
    }
}
