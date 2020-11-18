/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Pata behaviour
*/

#pragma once

#include "../../core/ABehaviour.hpp"
#include "../../core/components/PositionComponent.hpp"
#include "../CollideGroups.hpp"

#include <cmath>
#include <iostream>

namespace rtype::server {

    class BugBehaviour : public ABehaviour {
      private:
        PositionComponent *position_ = nullptr;

        std::size_t amplitude_ = 8;
        std::size_t longitude_ = 20;
        int accuracy_ = 100;

        float stepInX_ = 0.9;

        long totalElapsedTime_ = 0;
        long rate_ = 16;

        int limiteMinInX_ = 0;

        std::size_t initInY_ = 0;


      public:
        void onInit() override
        {
        }

        void onUpdate(long elapsedTime) override
        {
            if (this->position_ == nullptr) {
                this->position_ = this->getComponent<PositionComponent>();
                this->initInY_ = this->position_->y;
            }
            this->totalElapsedTime_ += elapsedTime;
            int step = this->totalElapsedTime_ / this->rate_;

            this->position_->x -= step * this->stepInX_;
            this->position_->y = this->initInY_ + (this->amplitude_ * sin(this->position_->x / this->longitude_));

            if (step)
                this->totalElapsedTime_ %= this->rate_;
            if (this->position_->x < this->limiteMinInX_)
                this->destroyEntity();
        }

        void onCollide(const CollisionData &collision) override
        {
            if (collision.other.collideGroup == COLLIDE_GROUP_PLAYERS) {
                this->takeDamage(1);
            }
        }
    };
}
