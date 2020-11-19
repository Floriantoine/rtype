/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** InputComponent
*/

#pragma once

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include "engine/core/Vector2.hpp"
#include "engine/core/ecs/component/Component.hpp"
#include "engine/core/ecs/entity/Entity.hpp"
#include "nlohmann/json.hpp"

namespace rtype::client {

    class InputComponent : public Component<InputComponent> {
      public:
        std::string string { "" };
        std::shared_ptr<sf::Font> font;
        int size { 30 };
        Vector2<float> offset;
        sf::Text text;
        int max;

      public:
        InputComponent() = default;
        InputComponent(std::string string, std::shared_ptr<sf::Font> font, int size, Vector2<float> offset, int max);

        static void factory(const std::shared_ptr<Entity> &entity, nlohmann::json body);
    };
}