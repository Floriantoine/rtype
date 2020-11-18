/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** RenderSystem
*/

#pragma once

#include "../Game.hpp"
#include "../components/ColorComponent.hpp"
#include "../components/TextComponent.hpp"
#include "engine/core/components/PositionComponent.hpp"
#include "engine/core/systems/ARenderSystem.hpp"

namespace rtype::client {
    class TextSystem : public ARenderSystem {
      public:
        TextSystem();
        ~TextSystem() = default;

        void update(long elapsedTime) override;
    };
};