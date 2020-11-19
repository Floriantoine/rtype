/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** SpriteComponent
*/

#pragma once

#include "../ecs/component/Component.hpp"
#include "../ecs/entity/Entity.hpp"
#include "nlohmann/json.hpp"

#include "../AssetLoader.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Sprite.hpp"

#include <memory>
#include <string>

namespace rtype {

    class SpriteComponent : public Component<SpriteComponent> {
      public:
        std::shared_ptr<sf::Texture> texture;
        sf::IntRect rect;
        sf::Sprite sprite;

      public:
        SpriteComponent() = default;
        SpriteComponent(const std::shared_ptr<sf::Texture> &texture, sf::IntRect rect)
            : texture { texture }
            , rect { rect }
            , sprite(*texture.get(), rect)
        {}

        static void factory(const std::shared_ptr<Entity> &entity, const nlohmann::json &body)
        {
            std::string texturePath { "" };
            int left { 0 };
            int top { 0 };
            int width { 0 };
            int height { 0 };

            auto texturePathJson = body.find("texture");
            if (texturePathJson != body.end()) {
                texturePathJson->get_to(texturePath);
            }
            auto leftJson = body.find("left");
            if (leftJson != body.end()) {
                leftJson->get_to(left);
            }
            auto topJson = body.find("top");
            if (topJson != body.end()) {
                topJson->get_to(top);
            }
            auto widthJson = body.find("width");
            if (widthJson != body.end()) {
                widthJson->get_to(width);
            }
            auto heightJson = body.find("height");
            if (heightJson != body.end()) {
                heightJson->get_to(height);
            }

            entity->addComponent<SpriteComponent>(
                AssetLoader::getTexture(texturePath),
                sf::IntRect(left, top, width, height));
        }
    };
}