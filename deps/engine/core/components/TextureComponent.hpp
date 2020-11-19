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

    class TextureComponent : public Component<TextureComponent> {
      public:
        std::string path { "" };
        std::size_t x { 0 };
        std::size_t y { 0 };
        std::size_t width { 0 };
        std::size_t height { 0 };

      public:
        TextureComponent() = default;
        TextureComponent(std::string path, std::size_t x, std::size_t y,
            std::size_t width, std::size_t height)
            : path { path }
            , x { x }
            , y { y }
            , width { width }
            , height { height } {};

        static void factory(const std::shared_ptr<Entity> &entity, const nlohmann::json &body)
        {
            std::string path { "" };
            std::size_t x { 0 };
            std::size_t y { 0 };
            std::size_t width { 0 };
            std::size_t height { 0 };

            auto pathJson = body.find("path");
            if (pathJson != body.end()) {
                pathJson->get_to(path);
            }
            auto xJson = body.find("x");
            if (xJson != body.end()) {
                xJson->get_to(x);
            }
            auto yJson = body.find("y");
            if (yJson != body.end()) {
                yJson->get_to(y);
            }
            auto widthJson = body.find("width");
            if (widthJson != body.end()) {
                widthJson->get_to(width);
            }
            auto heightJson = body.find("height");
            if (heightJson != body.end()) {
                heightJson->get_to(height);
            }

            entity->addComponent<TextureComponent>(path, x, y, width, height);
        }
    };
}