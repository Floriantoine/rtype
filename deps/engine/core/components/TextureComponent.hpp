/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** ATextureComponent
*/

#pragma once

#include "../ecs/component/Component.hpp"

#include <string>

namespace rtype {

    class TextureComponent : public Component<TextureComponent> {
      public:
        std::string path { "" };
        std::string file { "" };

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
    };
}