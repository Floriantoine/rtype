/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** AnimationSystem
*/

#pragma once

#include "engine/core/systems/AAnimationSystem.hpp"

namespace rtype::client {
    class AnimationSystem : public AAnimationSystem {
      public:
        AnimationSystem() = default;
        ~AnimationSystem() = default;

        void update(long elapsedTime) override;
    };
}