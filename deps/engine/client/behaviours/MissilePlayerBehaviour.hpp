/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** MissilePlayerComponent
*/

#pragma once

/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Player Script Component
*/

#pragma once

#include "../../core/ABehaviour.hpp"
#include "../../core/components/PositionComponent.hpp"
#include "../CollideGroups.hpp"

#include <cmath>
#include <iostream>

namespace rtype {

    class MissilePlayerBehaviour : public ABehaviour {
      private:
        PositionComponent *position_ = nullptr;

        long totalElapsedTime_ = 0;
        long stepInX_ = 10;
        long rate_ = 20;

      public:
        void onUpdate(long elapsedTime) override
        {
            if (this->position_ == nullptr) {
                this->position_ = this->getComponent<PositionComponent>();
            }
            this->totalElapsedTime_ += elapsedTime;
            int step = this->totalElapsedTime_ / this->rate_;

            this->position_->x += step * this->stepInX_;
            if (step)
                this->totalElapsedTime_ %= this->rate_;
        }

        void onCollide(const CollisionData &collision) override
        {
            if (collision.other.collideGroup != COLLIDE_GROUP_PLAYERS) {
                this->takeDamage(1);
            }
        }

        void onViewLeave() override
        {
            this->takeDamage(this->getHealth());
        }
    };
}