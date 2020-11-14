/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** AAnimationSystem
*/

#pragma once

#include "engine/core/ecs/system/ASystem.hpp"

namespace rtype {

    class AAnimationSystem : public ASystem
    {
      protected:
        AAnimationSystem() : ASystem() {};
        ~AAnimationSystem() = default;

      public:
        virtual void update() = 0;
    };
}
