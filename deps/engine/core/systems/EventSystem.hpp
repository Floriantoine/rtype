/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Event System
*/

#pragma once

#include "../../client/Game.hpp"
#include "../components/AScriptComponent.hpp"
#include "../ecs/system/ASystem.hpp"
#include "SFML/Window/Event.hpp"

namespace rtype {

    class EventSystem : public ASystem {
      public:
        void update(long elapsedTime)
        {
            sf::Window *window = client::Game::getInstance().getWindow();
            sf::Event evt;

            while (window->pollEvent(evt)) {
                this->handleCloseEvent(evt);
                this->handleMouseButtonPressedEvents(evt);
                this->handleMouseButtonReleasedEvents(evt);
                this->handleKeyPressedEvents(evt);
                this->handleKeyReleasedEvents(evt);
            }
        }

        void handleCloseEvent(const sf::Event &evt)
        {
            if (evt.type == sf::Event::EventType::Closed) {
                client::Game::getInstance().getWindow()->close();
                client::Game::getInstance().stop();
            }
        }

        void handleMouseButtonPressedEvents(const sf::Event &evt)
        {
            if (evt.type == sf::Event::EventType::MouseButtonPressed) {
                this->componentManager_->apply<AScriptComponent>([&](AScriptComponent *component) {
                    component->onMouseButtonPressed(evt);
                });
            }
        }

        void handleMouseButtonReleasedEvents(const sf::Event &evt)
        {
            if (evt.type == sf::Event::EventType::MouseButtonReleased) {
                this->componentManager_->apply<AScriptComponent>([&](AScriptComponent *component) {
                    component->onMouseButtonReleased(evt);
                });
            }
        }

        void handleKeyPressedEvents(const sf::Event &evt)
        {
            if (evt.type == sf::Event::EventType::KeyPressed) {
                this->componentManager_->apply<AScriptComponent>([&](AScriptComponent *component) {
                    component->onKeyPressed(evt);
                });
            }
        }

        void handleKeyReleasedEvents(const sf::Event &evt)
        {
            if (evt.type == sf::Event::EventType::KeyReleased) {
                this->componentManager_->apply<AScriptComponent>([&](AScriptComponent *component) {
                    component->onKeyReleased(evt);
                });
            }
        }
    };

}
