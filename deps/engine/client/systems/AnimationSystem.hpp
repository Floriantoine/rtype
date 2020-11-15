/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** AnimationSystem
*/

#pragma once

#include "../../core/components/AnimationComponent.hpp"
#include "../../core/systems/AAnimationSystem.hpp"

namespace rtype::client {
    class AnimationSystem : public AAnimationSystem {
      public:
        AnimationSystem() = default;
        ~AnimationSystem() = default;

        void update(long elapsedTime) override
        {
            this->componentManager_->apply<AnimationComponent>([&](AnimationComponent *anim) {
                if (anim->rate == 0)
                    return;
                anim->totalElapsedTime += elapsedTime;
                int step = anim->totalElapsedTime / anim->rate;

                if (step == 0)
                    return;
                anim->totalElapsedTime %= anim->rate;
                anim->currentFrame = (anim->currentFrame + step) % anim->totalFrame;
            });
        };
    };
};