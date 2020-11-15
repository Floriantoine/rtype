/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** HitHandler
*/

#include "HitHandler.hpp"

namespace rtype::server {
    HitHandler::HitHandler(std::vector<Player> &players)
        : AHandlerUDP(players)
    {
    }

    void HitHandler::response(const Network::UdpPackage &package)
    {
    }

    void HitHandler::request(const Network::UdpPackage &package)
    {
    }
}
