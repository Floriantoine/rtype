/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** MissilePlayerComponent
*/

#pragma once

#include "core/ABehaviour.hpp"
#include "core/components/PositionComponent.hpp"

namespace rtype::client {
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
