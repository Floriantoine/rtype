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
#include <string>

namespace rtype {

    class MissileComponent : public Component<MissileComponent> {
      public:
        nlohmann::json missileBody;
        std::size_t rate { 0 };

      public:
        MissileComponent() = default;
        MissileComponent(nlohmann::json missileBody, std::size_t rate)
            : missileBody { missileBody }
            , rate { rate } {};

        static void factory(const std::shared_ptr<Entity> &entity, nlohmann::json body)
        {
            nlohmann::json missileBody;
            std::size_t rate { 0 };

            auto missileBodyJson = body.find("missileBody");
            if (missileBodyJson != body.end()) {
                missileBodyJson->get_to(missileBody);
            }
            auto rateJson = body.find("rate");
            if (rateJson != body.end()) {
                rateJson->get_to(rate);
            }

            entity->addComponent<MissileComponent>(missileBody, rate);
        }
    };
}