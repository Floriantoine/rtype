/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** MissilePlayerComponent
*/

#pragma once

#include "engine/core/ABehaviour.hpp"
#include "engine/core/components/PositionComponent.hpp"

#include <cmath>
#include <iostream>

namespace rtype::server {

    class MissilePlayerBehaviour : public ABehaviour {
      private:
        PositionComponent *position_ = nullptr;

        long totalElapsedTime_ = 0;
        long stepInX_ = 10;
        long rate_ = 20;

      public:
        void onUpdate(long elapsedTime) override;
        void onCollide(const CollisionData &collision) override;
        void onViewLeave() override;
    };

}
