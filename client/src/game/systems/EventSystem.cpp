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
#include "engine/core/components/CollideBoxComponent.hpp"
#include "engine/core/physics/CollisionChecker.hpp"
#include "game/Game.hpp"

namespace rtype::client {
    void EventSystem::update(long elapsedTime)
    {
        sf::Window *window = client::Game::getInstance().getWindow();
        sf::Event evt;

        while (window->pollEvent(evt)) {
            this->handleCloseEvent(evt);
            this->handleMouseMove(evt);
            this->handleMouseButtonPressedEvents(evt);
            this->handleMouseButtonReleasedEvents(evt);
            this->handleKeyPressedEvents(evt);
            this->handleKeyReleasedEvents(evt);
        }
    }

    void EventSystem::handleCloseEvent(const sf::Event &evt)
    {
        if (evt.type != sf::Event::EventType::Closed)
            return;
        Game::getInstance().getWindow()->close();
        Game::getInstance().stop();
    }

    void EventSystem::handleMouseMove(const sf::Event &evt)
    {
        if (evt.type != sf::Event::EventType::MouseMoved)
            return;
        this->componentManager_->apply<BehaviourComponent>([&](BehaviourComponent *holder) {
            if (!holder->getEntity()->getVisibility())
                return;
            const auto &behaviour = holder->getBehaviour<ABehaviour>();
            if (behaviour == nullptr)
                return;
            behaviour->onMouseMove(evt);
            const auto &collideBox = holder->getEntity()->getComponent<CollideBoxComponent>();
            if (collideBox == nullptr)
                return;
            Vector2<float> cursorPosition(evt.mouseMove.x, evt.mouseMove.y);
            if (CollisionChecker::collides(collideBox->box, cursorPosition))
                behaviour->onMouseHover(evt);
        });
    }

    void EventSystem::handleMouseButtonPressedEvents(const sf::Event &evt)
    {
        if (evt.type != sf::Event::EventType::MouseButtonPressed)
            return;
        this->componentManager_->apply<BehaviourComponent>([&](BehaviourComponent *holder) {
            if (!holder->getEntity()->getVisibility())
                return;
            const auto &behaviour = holder->getBehaviour<ABehaviour>();
            if (behaviour == nullptr)
                return;
            behaviour->onMouseButtonPressed(evt);
            const auto &collideBox = holder->getEntity()->getComponent<CollideBoxComponent>();
            if (collideBox == nullptr)
                return;
            Vector2<float> cursorPosition(evt.mouseButton.x, evt.mouseButton.y);
            if (CollisionChecker::collides(collideBox->box, cursorPosition))
                behaviour->onMouseClick(evt);
        });
    }

    void EventSystem::handleMouseButtonReleasedEvents(const sf::Event &evt)
    {
        if (evt.type != sf::Event::EventType::MouseButtonReleased)
            return;
        this->componentManager_->apply<BehaviourComponent>([&](BehaviourComponent *holder) {
            if (!holder->getEntity()->getVisibility())
                return;
            const auto &behaviour = holder->getBehaviour<ABehaviour>();
            if (behaviour != nullptr)
                holder->getBehaviour<ABehaviour>()->onMouseButtonReleased(evt);
        });
    }

    void EventSystem::handleKeyPressedEvents(const sf::Event &evt)
    {
        if (evt.type != sf::Event::EventType::KeyPressed)
            return;
        this->componentManager_->apply<BehaviourComponent>([&](BehaviourComponent *holder) {
            if (!holder->getEntity()->getVisibility())
                return;
            const auto &behaviour = holder->getBehaviour<ABehaviour>();
            if (behaviour != nullptr)
                holder->getBehaviour<ABehaviour>()->onKeyPressed(evt);
        });
    }

    void EventSystem::handleKeyReleasedEvents(const sf::Event &evt)
    {
        if (evt.type != sf::Event::EventType::KeyReleased)
            return;
        this->componentManager_->apply<BehaviourComponent>([&](BehaviourComponent *holder) {
            if (!holder->getEntity()->getVisibility())
                return;
            const auto &behaviour = holder->getBehaviour<ABehaviour>();
            if (behaviour != nullptr)
                behaviour->onKeyReleased(evt);
        });
    }
}
