/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Health Component
*/

#pragma once

#include "../ecs/component/Component.hpp"
#include "../ecs/entity/Entity.hpp"
#include "nlohmann/json.hpp"

namespace rtype {

    class HealthComponent : public Component<HealthComponent> {
      public:
        int health { 1 };

      public:
        HealthComponent() = default;
        HealthComponent(int health)
            : health { health }
        { }

        static void factory(const std::shared_ptr<Entity> &entity, const nlohmann::json &body)
        {
            std::size_t health { 0 };

            auto healthJson = body.find("health");
            if (healthJson != body.end()) {
                healthJson->get_to(health);
            }

            entity->addComponent<HealthComponent>(health);
        }
    };
}