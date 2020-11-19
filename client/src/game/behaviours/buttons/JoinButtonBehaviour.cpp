/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** JoinButtonBehaviour
*/

#include "JoinButtonBehaviour.hpp"
#include "game/behaviours/NavButtonBehaviour.hpp"
#include "game/Game.hpp"

#include <iostream>

namespace rtype::client {

void JoinButtonBehaviour::onMouseClick(const sf::Event &evt)
{
    const std::string &lobbyId = Game::getInstance().getLobbyId();

    if (lobbyId.size() != 6)
        return;
    // TODO: Send START request with lobbyId param
    std::cout << "requesting: ASK_JOIN (" << lobbyId << ")" << std::endl;
    // if (request succeeded) {
    //     // Redirect
        NavButtonBehaviour::onMouseClick(evt);
    // }
}

}