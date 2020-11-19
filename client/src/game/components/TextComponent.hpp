/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** TextComponent
*/

#pragma once

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include "engine/core/ecs/component/Component.hpp"
#include "engine/core/ecs/entity/Entity.hpp"
#include "nlohmann/json.hpp"

namespace rtype::client {

    class TextComponent : public Component<TextComponent> {
      public:
        std::string string { "" };
        std::shared_ptr<sf::Font> font;
        int size { 30 };
        sf::Text text;

      public:
        TextComponent() = default;
        TextComponent(const std::string &string, const std::shared_ptr<sf::Font> &font, int size);

        static void factory(const std::shared_ptr<Entity> &entity, const nlohmann::json &body);
    };
}