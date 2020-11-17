/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** SpawnHandler
*/

#include "SpawnHandler.hpp"

namespace rtype::server {
    SpawnHandler::SpawnHandler(std::vector<Player> &players)
        : AHandlerUDP(players)
    {
    }

    void SpawnHandler::response(const Network::UdpPackage &package)
    {
    }

    void SpawnHandler::request(const Network::UdpPackage &package)
    {
    }
}
