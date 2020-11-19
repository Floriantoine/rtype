/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** CreateButtonBehaviour
*/

#include "CreateButtonBehaviour.hpp"
#include "game/behaviours/NavButtonBehaviour.hpp"

#include <iostream>

namespace rtype::client {

void CreateButtonBehaviour::onMouseClick(const sf::Event &evt)
{
    // TODO: Send CREATE request
    std::cout << "requesting: CREATE" << std::endl;
    // if (request succeeded) {
    //     // Redirect
        NavButtonBehaviour::onMouseClick(evt);
    // }
}

}