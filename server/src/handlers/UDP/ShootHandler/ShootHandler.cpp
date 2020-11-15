/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** ShootHandler
*/

#include "ShootHandler.hpp"

namespace rtype::server {
    ShootHandler::ShootHandler(std::vector<Player> &players)
        : AHandlerUDP(players)
    {
    }

    void ShootHandler::response(const BPC::Package &package)
    {
    }

    void ShootHandler::request(const BPC::Package &package)
    {
    }
}
