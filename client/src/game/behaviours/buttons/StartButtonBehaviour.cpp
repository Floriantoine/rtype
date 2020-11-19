/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** StartButtonBehaviour
*/

#include "StartButtonBehaviour.hpp"
#include "game/behaviours/NavButtonBehaviour.hpp"

#include <iostream>

namespace rtype::client {

void StartButtonBehaviour::onMouseClick(const sf::Event &evt)
{
    // TODO: Send START request
    std::cout << "requesting: START" << std::endl;
    // if (request succeeded) {
    //     // Redirect
        NavButtonBehaviour::onMouseClick(evt);
    // }
}

}