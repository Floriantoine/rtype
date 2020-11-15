/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Event System
*/

#pragma once

#include "../components/AScriptComponent.hpp"
#include "../ecs/system/ASystem.hpp"
#include "../../client/Game.hpp"
#include <SFML/Window/Event.h>

namespace rtype {

    class EventSystem : public ASystem {
      public:
        void update(long elapsedTime)
        {
            sf::Window *window = client::Game::getInstance().getWindow();
            sf::Event evt;

            while (window->pollEvent(evt)) {
                if (evt.type == sf::Event::EventType::Closed) {
                    window->close();
                    client::Game::getInstance().stop();
                }
            }
        }
    };

}
