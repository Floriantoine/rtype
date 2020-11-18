/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Event System
*/

#include "EventSystem.hpp"

#include "SFML/Window/Event.hpp"
#include "game/ABehaviour.hpp"
#include "engine/core/components/BehaviourComponent.hpp"
#include "game/Game.hpp"

namespace rtype::client {
    void EventSystem::update(long elapsedTime)
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

    void EventSystem::handleCloseEvent(const sf::Event &evt)
    {
        if (evt.type == sf::Event::EventType::Closed) {
            Game::getInstance().getWindow()->close();
            Game::getInstance().stop();
        }
    }

    void EventSystem::handleMouseButtonPressedEvents(const sf::Event &evt)
    {
        if (evt.type == sf::Event::EventType::MouseButtonPressed) {
            this->componentManager_->apply<BehaviourComponent>([&](BehaviourComponent *holder) {
                if (!holder->getEntity()->getVisibility())
                    return;
                const std::shared_ptr<ABehaviour> &behaviour = holder->getBehaviour<ABehaviour>();
                if (behaviour != nullptr)
                    behaviour->onMouseButtonPressed(evt);
            });
        }
    }

    void EventSystem::handleMouseButtonReleasedEvents(const sf::Event &evt)
    {
        if (evt.type == sf::Event::EventType::MouseButtonReleased) {
            this->componentManager_->apply<BehaviourComponent>([&](BehaviourComponent *holder) {
                if (!holder->getEntity()->getVisibility())
                    return;
                const std::shared_ptr<ABehaviour> &behaviour = holder->getBehaviour<ABehaviour>();
                if (behaviour != nullptr)
                    holder->getBehaviour<ABehaviour>()->onMouseButtonReleased(evt);
            });
        }
    }

    void EventSystem::handleKeyPressedEvents(const sf::Event &evt)
    {
        if (evt.type == sf::Event::EventType::KeyPressed) {
            this->componentManager_->apply<BehaviourComponent>([&](BehaviourComponent *holder) {
                if (!holder->getEntity()->getVisibility())
                    return;
                const std::shared_ptr<ABehaviour> &behaviour = holder->getBehaviour<ABehaviour>();
                if (behaviour != nullptr)
                    holder->getBehaviour<ABehaviour>()->onKeyPressed(evt);
            });
        }
    }

    void EventSystem::handleKeyReleasedEvents(const sf::Event &evt)
    {
        if (evt.type == sf::Event::EventType::KeyReleased) {
            this->componentManager_->apply<BehaviourComponent>([&](BehaviourComponent *holder) {
                if (!holder->getEntity()->getVisibility())
                    return;
                const auto &behaviour = holder->getBehaviour<ABehaviour>();
                if (behaviour != nullptr)
                    behaviour->onKeyReleased(evt);
            });
        }
    }
}
