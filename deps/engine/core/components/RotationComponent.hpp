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

    class RotationComponent : public Component<RotationComponent> {
      public:
        int degree { 0 };

      public:
        RotationComponent() = default;
        RotationComponent(int degree)
            : degree { degree } {};

        static void factory(const std::shared_ptr<Entity> &entity, nlohmann::json body)
        {
            std::size_t degree { 0 };

            auto degreeJson = body.find("degree");
            if (degreeJson != body.end()) {
                degreeJson->get_to(degree);
            }

            entity->addComponent<RotationComponent>(degree);
        }
    };
}