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

        void onUpdate() override
        {
        }

        void onKeyPressed(const sf::Event::KeyEvent &event) override
        {
            std::cout << "pressed key" << event.code << std::endl;
        }

        void onMouseButtonPressed(const sf::Event::MouseButtonEvent &event) override
        {
            std::cout << "clicked (" << event.x << ":" << event.y << ")" << std::endl;
        }

        void onCollide() override
        {
        }
    };

}
