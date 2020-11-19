/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** RenderSystem
*/

#include "BackgroundSystem.hpp"

#include "engine/core/components/BackgroundComponent.hpp"
#include "engine/core/components/PositionComponent.hpp"
#include "engine/core/systems/ARenderSystem.hpp"
#include "game/Game.hpp"

namespace rtype::client {
    void BackgroundSystem::update(long elapsedTime)
    {
        Entity *cameraEntity = this->getCamera();
        PositionComponent *cameraPosition = nullptr;

        if (!!cameraEntity && !(cameraPosition = cameraEntity->getComponent<PositionComponent>()))
            return;
        this->componentManager_->apply<BackgroundComponent>([&](BackgroundComponent *back) {
            PositionComponent *position = back->getEntity()->getComponent<PositionComponent>();

            if (position != nullptr) {
                back->sprite.setPosition(position->x - cameraPosition->x, position->y - cameraPosition->y);
            }
            Game::getInstance().getWindow()->draw(back->sprite);
        });
    }
}