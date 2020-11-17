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

    class CollideGroupComponent : public Component<CollideGroupComponent> {
      public:
        int group { -1 };

      public:
        CollideGroupComponent() = default;
        CollideGroupComponent(int group)
            : group { group }
        {}

        static void factory(const std::shared_ptr<Entity> &entity, nlohmann::json body)
        {
            int group { -1 };

            auto xJson = body.find("group");
            if (xJson != body.end()) {
                xJson->get_to(group);
            }

            entity->addComponent<CollideGroupComponent>(group);
        }
    };
}