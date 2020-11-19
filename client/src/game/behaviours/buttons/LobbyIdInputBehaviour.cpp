/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** LobbyIdInputBehaviour
*/

#include "LobbyIdInputBehaviour.hpp"
#include "game/Game.hpp"

#include <iostream>

namespace rtype::client {

void LobbyIdInputBehaviour::onChange(const std::string &value)
{
    Game::getInstance().setLobbyId(value);
}

}