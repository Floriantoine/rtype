/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Pata behaviour
*/

#pragma once

#include "engine/core/components/PositionComponent.hpp"
#include "engine/core/components/RotationComponent.hpp"
#include "game/ABehaviour.hpp"

namespace rtype::client {
    class BugBehaviour : public ABehaviour {
      private:
        PositionComponent *position_ = nullptr;
        RotationComponent *rotation_ = nullptr;

        std::size_t amplitude_ = 8;
        std::size_t longitude_ = 20;
        int accuracy_ = 100;

        float stepInX_ = 0.9;

        long totalElapsedTime_ = 0;
        long rate_ = 16;

        int limiteMinInX_ = 0;

        std::size_t initInY_ = 0;

      public:
        void onUpdate(long elapsedTime) override;
        void onCollide(const CollisionData &collision) override;
    };
}
