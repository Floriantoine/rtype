/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** RenderSystem
*/

#include "game/systems/SpriteSystem.hpp"
#include "game/Game.hpp"

namespace rtype::client {

    SpriteSystem::SpriteSystem()
        : ARenderSystem() {};

    void SpriteSystem::update(long elapsedTime)
    {
        Entity *cameraEntity = this->getCamera();
        PositionComponent *cameraPosition = nullptr;

        if (!!cameraEntity && !(cameraPosition = cameraEntity->getComponent<PositionComponent>()))
            return;

        this->componentManager_->apply<SpriteComponent>([&](SpriteComponent *sprite) {
            if (!sprite->getEntity()->getVisibility())
                return;
            PositionComponent *position = sprite->getEntity()->getComponent<PositionComponent>();
            AnimationComponent *animation = sprite->getEntity()->getComponent<AnimationComponent>();
            RotationComponent *rotation = sprite->getEntity()->getComponent<RotationComponent>();

            if (position != nullptr) {
                sprite->sprite.setPosition(position->x - cameraPosition->x, position->y - cameraPosition->y);
            }
            if (animation != nullptr) {
                sprite->rect.left = sprite->rect.width * animation->currentFrame;
                sprite->sprite.setTextureRect(sprite->rect);
            }
            if (rotation != nullptr) {
                sprite->sprite.setOrigin(sprite->rect.width / 2, sprite->rect.height / 2);
                sprite->sprite.setRotation(rotation->degree);
            }
            Game::getInstance().getWindow()->draw(sprite->sprite);
            sprite->sprite.setOrigin(0, 0);
        });
    }
}
