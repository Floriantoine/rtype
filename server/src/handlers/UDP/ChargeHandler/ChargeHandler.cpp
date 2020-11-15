/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** ChargeHandler
*/

#include "ChargeHandler.hpp"

namespace rtype::server {
    ChargeHandler::ChargeHandler(std::vector<Player> &players) 
        : AHandlerUDP(players)
    {
    }

    void ChargeHandler::response(const BPC::Package &package)
    {
    }

    void ChargeHandler::request(const BPC::Package &package)
    {
    }
}
