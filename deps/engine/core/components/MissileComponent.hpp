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
        MissileComponent(const nlohmann::json &missileBody, std::size_t rate)
            : missileBody ( std::move(missileBody) )
            , rate { rate }
        { }

        static void factory(const std::shared_ptr<Entity> &entity, const nlohmann::json &body)
        {
            nlohmann::json missileBody;
            std::size_t rate { 0 };

            auto missileBodyJson = body.find("body");
            if (missileBodyJson != body.end()) {
                missileBody = *missileBodyJson;
            }
            auto rateJson = body.find("rate");
            if (rateJson != body.end()) {
                rateJson->get_to(rate);
            }

            entity->addComponent<MissileComponent>(missileBody, rate);
        }
    };
}