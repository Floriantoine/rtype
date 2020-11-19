/*
** EPITECH PROJECT, 2020
** *
** File description:
** ColorComponent
*/

#pragma once

#include "SFML/Graphics/Color.hpp"
#include "engine/core/ecs/component/Component.hpp"
#include "engine/core/ecs/entity/Entity.hpp"
#include "nlohmann/json.hpp"

namespace rtype::client {

    class ColorComponent : public Component<ColorComponent> {
      public:
        int red;
        int green;
        int blue;
        int alpha;
        bool outline;
        sf::Color color;

      public:
        ColorComponent() = default;
        ColorComponent(int red, int green, int blue, int alpha, bool outline);

        static void factory(const std::shared_ptr<Entity> &entity, const nlohmann::json &body);
    };
}
