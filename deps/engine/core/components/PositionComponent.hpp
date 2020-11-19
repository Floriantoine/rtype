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

    class PositionComponent : public Component<PositionComponent> {
      public:
        float x { 0 };
        float y { 0 };

      public:
        PositionComponent() = default;
        PositionComponent(float x, float y)
            : x { x }
            , y { y } {};

        static void factory(const std::shared_ptr<Entity> &entity, nlohmann::json body)
        {
            float x { 0 };
            float y { 0 };

            auto xJson = body.find("x");
            if (xJson != body.end()) {
                xJson->get_to(x);
            }
            auto yJson = body.find("y");
            if (yJson != body.end()) {
                yJson->get_to(y);
            }

            entity->addComponent<PositionComponent>(x, y);
        }
    };
}