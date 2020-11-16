/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** DestroyHandler
*/

#include "DestroyHandler.hpp"

namespace rtype::server {
    DestroyHandler::DestroyHandler(std::vector<Player> &players)
        : AHandlerUDP(players)
    {
    }

    void DestroyHandler::response(const Network::UdpPackage &package)
    {
    }

    void DestroyHandler::request(const Network::UdpPackage &package)
    {
    }
}
