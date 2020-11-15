/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Player Script Component
*/

#pragma once

#include "./AScriptComponent.hpp"

#include <SFML/Window/Event.hpp>
#include <iostream>

namespace rtype {

    class PlayerScriptComponent : public AScriptComponent {
      public:
        void onInit() override
        {
        }

        void onUpdate(long elapsedTime) override
        {
            static PositionComponent *position = this->getComponent<PositionComponent>();
        }

        void onKeyPressed(const sf::Event &event) override
        {
            std::cout << "pressed key" << event.key.code << std::endl;
        }

        void onMouseButtonPressed(const sf::Event &event) override
        {
            std::cout << "clicked (" << event.mouseButton.x << ":" << event.mouseButton.y << ")" << std::endl;
        }

        void onCollide() override
        {
        }
    };

}
