/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** GrabHandler
*/

#include "GrabHandler.hpp"

namespace rtype::server {
    GrabHandler::GrabHandler(std::vector<Player> &players)
        : AHandlerUDP(players)
    {
    }

    void GrabHandler::response(const Network::UdpPackage &package)
    {
    }

    void GrabHandler::request(const Network::UdpPackage &package)
    {
    }
}
