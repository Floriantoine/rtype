/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** InputSystem
*/

#include "InputSystem.hpp"

namespace rtype::client {

    InputSystem::InputSystem()
        : ARenderSystem() {};

    void InputSystem::update(long elapsedTime)
    {
        this->componentManager_->apply<InputComponent>([&](InputComponent *text) {
            PositionComponent *position = text->getEntity()->getComponent<PositionComponent>();
            ColorComponent *color = text->getEntity()->getComponent<ColorComponent>();
            float realX = 0;
            float realY = 0;

            if (position != nullptr) {
                realX = position->x + text->offset.x;
                realY = position->y + text->offset.y;
                text->text.setPosition(realX, realY);
            }
            if (color != nullptr) {
                text->text.setFillColor(color->color);
                if (color->outline && position != nullptr) {
                    InputComponent text2 = *text;
                    text2.text.setPosition(realX + 2, realY);
                    text2.text.setFillColor(sf::Color(255, 255, 255));
                    client::Game::getInstance().getWindow()->draw(text2.text);
                }
            }
            client::Game::getInstance().getWindow()->draw(text->text);
        });
    }
}