/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** LeaveHandler
*/

#include "LeaveHandler.hpp"

namespace rtype::server {
    LeaveHandler::LeaveHandler(std::vector<Player> &players)
        : AHandlerUDP(players)
    {
    }

    void LeaveHandler::response(const Network::UdpPackage &package)
    {
    }

    void LeaveHandler::request(const Network::UdpPackage &package)
    {
    }
}
