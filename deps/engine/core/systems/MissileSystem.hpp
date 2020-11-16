/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** GravitationSystem
*/

#pragma once

#include "../components/MissileComponent.hpp"
#include "../ecs/system/ASystem.hpp"

#include <functional>

namespace rtype {

    class MissileSystem : public ASystem {
      private:
        std::function<void(MissileComponent *)> function = [](MissileComponent *position) {
        };

      public:
        MissileSystem()
            : ASystem() {};
        ~MissileSystem() = default;

        void update(long elapsedTime) override
        {
            this->componentManager_->apply<MissileComponent>(function);
        };
    };
}
