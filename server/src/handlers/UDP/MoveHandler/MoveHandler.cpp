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

    void MoveHandler::response(const Network::UdpPackage &package)
    {
    }

    void MoveHandler::request(const Network::UdpPackage &package)
    {
    }
}
