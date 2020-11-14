/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** ATextureComponent
*/

#pragma once

#include "../ecs/component/Component.hpp"

namespace rtype {

    class PositionComponent : public Component<PositionComponent> {
      public:
        std::size_t x { 0 };
        std::size_t y { 0 };

      public:
        PositionComponent() = default;
        PositionComponent(std::size_t x, std::size_t y)
            : x { x }
            , y { y } {};
    };
}