/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** TextSystem
*/

#include "TextSystem.hpp"

namespace rtype::client {
    TextSystem::TextSystem()
        : ARenderSystem() {};

    void TextSystem::update(long elapsedTime)
    {
        this->componentManager_->apply<TextComponent>([&](TextComponent *text) {
            PositionComponent *position = text->getEntity()->getComponent<PositionComponent>();
            ColorComponent *color = text->getEntity()->getComponent<ColorComponent>();

            if (position != nullptr) {
                text->text.setPosition(position->x, position->y);
            }
            if (color != nullptr) {
                text->text.setFillColor(color->color);
                TextComponent text2 = *text;
                if (color->outline) {
                    text2.text.setPosition(position->x + 2, position->y);
                    text2.text.setFillColor(sf::Color(255, 255, 255));
                    client::Game::getInstance().getWindow()->draw(text2.text);
                }
            }
            client::Game::getInstance().getWindow()->draw(text->text);
        });
    }
};