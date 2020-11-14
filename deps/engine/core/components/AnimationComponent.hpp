/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** ATextureComponent
*/

#pragma once

#include "../ecs/component/Component.hpp"
#include "../ecs/entity/Entity.hpp"
#include "nlohmann/json.hpp"

#include <memory>

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

        static void factory(const std::shared_ptr<Entity> &entity, nlohmann::json body)
        {
            std::size_t currentFrame { 0 };
            std::size_t totalFrame { 0 };

            auto currentJson = body.find("currentFrame");
            if (currentJson != body.end()) {
                currentJson->get_to(currentFrame);
            }
            auto totalJson = body.find("totalFrame");
            if (totalJson != body.end()) {
                totalJson->get_to(totalFrame);
            }

            entity->addComponent<AnimationComponent>(currentFrame, totalFrame);
        }
    };
}