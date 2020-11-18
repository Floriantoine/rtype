/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** GameStateHandler
*/

#include "GameStateHandler.hpp"
#include "Protocol.hpp"
#include "engine/core/components/BehaviourComponent.hpp"
#include "types.hpp"

namespace rtype::client {
    GameStateHandler::GameStateHandler(GameClient &owner)
    : AHandlerUDP(owner)
    { }

    void GameStateHandler::receiveRequest(const BPC::Package &package)
    { } 

    void GameStateHandler::receiveResponse(const BPC::Package &package)
    { }
    
    BPC::Method GameStateHandler::getMethod() const
    {
        return BPC::GAME_STATE;
    }
}
