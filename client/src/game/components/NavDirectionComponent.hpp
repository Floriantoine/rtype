/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** NavDirectionComponent
*/

#pragma once

#include "engine/core/ecs/component/Component.hpp"
#include "engine/core/ecs/entity/Entity.hpp"
#include "nlohmann/json.hpp"

namespace rtype::client {

    class NavDirectionComponent : public Component<NavDirectionComponent> {
      public:
        std::string direction;

      public:
        NavDirectionComponent() = default;
        NavDirectionComponent(const std::string &direction);

        static void factory(const std::shared_ptr<Entity> &entity, nlohmann::json body);
    };

}