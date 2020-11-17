/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** RenderSystem
*/

#pragma once

#include "../../core/components/SpriteComponent.hpp"
#include "../../core/components/PositionComponent.hpp"
#include "../../core/components/AnimationComponent.hpp"
#include "../../core/components/RotationComponent.hpp"
#include "../../core/systems/ARenderSystem.hpp"

namespace rtype::client {
    class SpriteSystem : public ARenderSystem {
      public:
        SpriteSystem()
            : ARenderSystem() {};
        ~SpriteSystem() = default;

        void update(long elapsedTime) override
        {
            this->componentManager_->apply<SpriteComponent>([&](SpriteComponent *sprite) {
                PositionComponent *position = sprite->getEntity()->getComponent<PositionComponent>();
                AnimationComponent *animation = sprite->getEntity()->getComponent<AnimationComponent>();
                RotationComponent *rotation = sprite->getEntity()->getComponent<RotationComponent>();

                if (position != nullptr) {
                    sprite->sprite.setPosition(position->x, position->y);
                }
                if (animation != nullptr) {
                    sprite->rect.left = sprite->rect.width * animation->currentFrame;
                    sprite->sprite.setTextureRect(sprite->rect);
                }
                if (rotation != nullptr) {
                    sprite->sprite.setOrigin(sprite->rect.width / 2, sprite->rect.height / 2);
                    sprite->sprite.setRotation(rotation->degree);
                }
                client::Game::getInstance().getWindow()->draw(sprite->sprite);
                sprite->sprite.setOrigin(0, 0);
            });
        }
    };
};