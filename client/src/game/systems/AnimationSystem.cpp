/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** AnimationSystem
*/

#include "AnimationSystem.hpp"

#include "engine/core/components/AnimationComponent.hpp"

namespace rtype::client {
    void AnimationSystem::update(long elapsedTime)
    {
        this->componentManager_->apply<AnimationComponent>([&](AnimationComponent *anim) {
            if (!anim->getEntity()->getVisibility())
                return;
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
}