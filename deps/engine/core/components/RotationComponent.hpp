/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** ATextureComponent
*/

#pragma once

#include "../ecs/component/Component.hpp"

namespace rtype {

    class RotationComponent : public Component<RotationComponent> {
      public:
        int degree { 0 };

      public:
        RotationComponent() = default;
        RotationComponent(int degree)
            : degree { degree } {};
    };
}