/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** RenderSystem
*/

#pragma once

#include "../Game.hpp"
#include "../components/ColorComponent.hpp"
#include "../components/InputComponent.hpp"
#include "engine/core/components/PositionComponent.hpp"
#include "engine/core/systems/ARenderSystem.hpp"

namespace rtype::client {
    class InputSystem : public ARenderSystem {
      public:
        InputSystem() = default;
        ~InputSystem() = default;

        void update(long elapsedTime) override;
    };
};