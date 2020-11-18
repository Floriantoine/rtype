/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** RenderSystem
*/

#pragma once

#include "engine/core/components/AnimationComponent.hpp"
#include "engine/core/components/PositionComponent.hpp"
#include "engine/core/components/RotationComponent.hpp"
#include "engine/core/components/SpriteComponent.hpp"
#include "engine/core/systems/ARenderSystem.hpp"

namespace rtype::client {

    class SpriteSystem : public ARenderSystem {
      public:
        SpriteSystem();
        ~SpriteSystem() = default;

        void update(long elapsedTime) override;
    };

}