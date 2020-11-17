/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** GameStateHandler
*/

#include "GameStateHandler.hpp"
#include "Protocol.hpp"

namespace rtype::server {
    GameStateHandler::GameStateHandler(Lobby &owner)
        : AHandlerUDP(owner)
    {
    }

    void GameStateHandler::receiveRequest(const Network::UdpPackage &package)
    {
    }

    void GameStateHandler::receiveResponse(const Network::UdpPackage &package)
    {
    }
    
    BPC::Method GameStateHandler::getMethod() const
    {
        return BPC::GAME_STATE;
    }
}
