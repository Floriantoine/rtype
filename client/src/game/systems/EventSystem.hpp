/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Event System
*/

#pragma once

#include "SFML/Window/Event.hpp"
#include "core/ecs/system/ASystem.hpp"

namespace rtype::client {
    class EventSystem : public ASystem {
      public:
        void update(long elapsedTime);
        void handleCloseEvent(const sf::Event &evt);
        void handleMouseMove(const sf::Event &evt);
        void handleMouseButtonPressedEvents(const sf::Event &evt);
        void handleMouseButtonReleasedEvents(const sf::Event &evt);
        void handleKeyPressedEvents(const sf::Event &evt);
        void handleKeyReleasedEvents(const sf::Event &evt);
    };
}
