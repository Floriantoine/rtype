/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Scant behaviour
*/

#pragma once

#include "core/ABehaviour.hpp"
#include "core/components/AnimationComponent.hpp"
#include "core/components/MissileComponent.hpp"
#include "core/components/PositionComponent.hpp"

namespace rtype::client {
    class ScantBehaviour : public ABehaviour {
      private:
        std::size_t amplitude_ = 400;
        int accuracy_ = 1;

        std::size_t stepInX_ = 1;

        long shootAnimElapsedTime_ = 0;
        long shootElapsedTime_ = 0;
        long totalElapsedTime_ = 0;

        bool isShooting_ = false;
        int shootAnimRate_ = 200;
        int shootRate_ = 1500;

        PositionComponent *position_ = nullptr;
        AnimationComponent *animation_ = nullptr;
        MissileComponent *missile_ = nullptr;
        std::size_t initInY_ = 0;

        void initComponents_();

      public:
        void onUpdate(long elapsedTime) override;
        void onCollide(const CollisionData &collision) override;
    };

}