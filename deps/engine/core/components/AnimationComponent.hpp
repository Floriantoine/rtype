/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** ATextureComponent
*/

#pragma once

#include "../ecs/component/Component.hpp"

namespace rtype {

    class AnimationComponent : public Component<AnimationComponent> {
      public:
        std::size_t currentFrame { 0 };
        std::size_t totalFrame { 0 };

      public:
        AnimationComponent() = default;
        AnimationComponent(std::size_t currentFrame, std::size_t totalFrame)
            : currentFrame { currentFrame }
            , totalFrame { totalFrame } {};
    };
}