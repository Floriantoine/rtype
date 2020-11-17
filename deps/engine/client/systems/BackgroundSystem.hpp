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
            this->componentManager_->apply<BackgroundComponent>([&](BackgroundComponent *back) {
                client::Game::getInstance().getWindow()->draw(back->sprite);
            });
        }
    };
};