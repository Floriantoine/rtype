/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** MissilePlayerComponent
*/

#include "game/CollideGroups.hpp"
#include "./MissilePlayerBehaviour.hpp"

namespace rtype::server {

    void MissilePlayerBehaviour::onUpdate(long elapsedTime)
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

    void MissilePlayerBehaviour::onCollide(const CollisionData &collision)
    {
        if (collision.other.collideGroup != COLLIDE_GROUP_PLAYERS) {
            this->takeDamage(1);
        }
    }

    void MissilePlayerBehaviour::onViewLeave()
    {
        this->takeDamage(this->getHealth());
    }

}