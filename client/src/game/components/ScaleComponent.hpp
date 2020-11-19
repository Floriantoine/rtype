/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** ScaleComponent
*/

#pragma once

#include "engine/core/ecs/component/Component.hpp"
#include "engine/core/ecs/entity/Entity.hpp"
#include "nlohmann/json.hpp"

namespace rtype::client {

    class ScaleComponent : public Component<ScaleComponent> {
      public:
        float x;
        float y;

      public:
        ScaleComponent() = default;
        ScaleComponent(float x, float y);

        static void factory(const std::shared_ptr<Entity> &entity, const nlohmann::json &body);
    };
}