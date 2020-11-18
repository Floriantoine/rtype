/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** RenderSystem
*/

#pragma once

#include "../../core/components/BackgroundComponent.hpp"
#include "../../core/components/PositionComponent.hpp"
#include "../../core/components/AnimationComponent.hpp"
#include "../../core/systems/ARenderSystem.hpp"

namespace rtype::client {
    class BackgroundSystem : public ARenderSystem {
      public:
        BackgroundSystem()
            : ARenderSystem() {};
        ~BackgroundSystem() = default;

        void update(long elapsedTime) override
        {
            Entity *cameraEntity = this->getCamera();
            PositionComponent *cameraPosition = nullptr;

            if (!!cameraEntity && !(cameraPosition = cameraEntity->getComponent<PositionComponent>()) )
                return;
            this->componentManager_->apply<BackgroundComponent>([&](BackgroundComponent *back) {
                PositionComponent *position = back->getEntity()->getComponent<PositionComponent>();

                if (position != nullptr) {
                    back->sprite.setPosition(position->x - cameraPosition->x, position->y - cameraPosition->y);
                }
                client::Game::getInstance().getWindow()->draw(back->sprite);
            });
        }
    };
};