/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** ATextureComponent
*/

#pragma once

#include "engine/core/ecs/component/Component.hpp"
#include "engine/core/ecs/entity/Entity.hpp"
#include "nlohmann/json.hpp"

namespace rtype::client {

    class AnimationComponent : public Component<AnimationComponent> {
      public:
        int currentFrame { 0 };
        int totalFrame { 0 };
        long totalElapsedTime { 0 };
        long rate { 0 };

      public:
        AnimationComponent() = default;
        AnimationComponent(int currentFrame, int totalFrame, long rate);

        static void factory(const std::shared_ptr<Entity> &entity, const nlohmann::json &body);
    };
}