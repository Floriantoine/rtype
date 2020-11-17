/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** PositionHandler
*/

#include "PositionHandler.hpp"

namespace rtype::server {
    PositionHandler::PositionHandler(std::vector<Player> &players)
        : AHandlerUDP(players)
    {
    }

    void PositionHandler::response(const Network::UdpPackage &package)
    {
    }

    void PositionHandler::request(const Network::UdpPackage &package)
    {
    }
}
