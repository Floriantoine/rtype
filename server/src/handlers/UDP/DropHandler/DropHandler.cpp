/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** DropHandler
*/

#include "DropHandler.hpp"

namespace rtype::server {
    DropHandler::DropHandler(std::vector<Player> &players)
        : AHandlerUDP(players)
    {
    }

    void DropHandler::response(const BPC::Package &package)
    {
    }

    void DropHandler::request(const BPC::Package &package)
    {
    }
}
