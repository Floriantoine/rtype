/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Pata behaviour
*/

#pragma once

#include "core/ABehaviour.hpp"
#include "core/components/PositionComponent.hpp"

#include <cstddef>

namespace rtype::client {
    class PataBehaviour : public ABehaviour {
      private:
        std::size_t amplitude_ = 15;
        int accuracy_ = 100;

        std::size_t stepInX_ = 5;

        long totalElapsedTime_ = 0;
        long rate_ = 16;

        int limiteMinInX_ = 0;

        PositionComponent *position_ = nullptr;
        std::size_t initInY_ = 0;

      public:
        void onUpdate(long elapsedTime) override;
        void onCollide(const CollisionData &collision) override;
    };
}