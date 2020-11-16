/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** ARenderSystem
*/

#pragma once

#include "../ecs/system/ASystem.hpp"

namespace rtype {
    class ARenderSystem : public ASystem {
      protected:
        ARenderSystem()
            : ASystem(ASystem::RENDER_SYSTEM_GROUP)
        { }
    };
}