/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** RenderSystem
*/

#pragma once

#include "../core/components/SpriteComponent.hpp"
#include "../core/components/PositionComponent.hpp"
#include "../core/components/AnimationComponent.hpp"
#include "../core/systems/ARenderSystem.hpp"

namespace rtype::client {
    class SpriteSystem : public ARenderSystem {
      public:
        SpriteSystem()
            : ARenderSystem() {};
        ~SpriteSystem() = default;

        void update(long elapsedTime) override
        {
            this->componentManager_->apply<SpriteComponent>([&](SpriteComponent *sprite) {
                PositionComponent *position = sprite->entity->getComponent<PositionComponent>();
                AnimationComponent *animation = sprite->entity->getComponent<AnimationComponent>();

                if (position != nullptr) {
                    sprite->sprite.setPosition(position->x, position->y);
                }
                if (animation != nullptr) {
                    sprite->rect.left = sprite->rect.width * animation->currentFrame;
                    sprite->sprite.setTextureRect(sprite->rect);
                }
                client::Game::getInstance().getWindow()->draw(sprite->sprite);
            });
        }
    };
};