/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Pata behaviour
*/

#include "game/CollideGroups.hpp"
#include "./BugBehaviour.hpp"

namespace rtype::server {

    void BugBehaviour::onUpdate(long elapsedTime)
    {
        if (this->position_ == nullptr) {
            this->position_ = this->getComponent<PositionComponent>();
            this->initInY_ = this->position_->y;
        }
        if (this->rotation_ == nullptr) {
            this->rotation_ = this->getComponent<RotationComponent>();
        }
        this->totalElapsedTime_ += elapsedTime;
        int step = this->totalElapsedTime_ / this->rate_;

        this->position_->x -= step * this->stepInX_;
        this->position_->y = this->initInY_ + (this->amplitude_ * sin(this->position_->x / this->longitude_));

        this->rotation_->degree = cos(this->position_->x / this->longitude_) * 35;

        if (step)
            this->totalElapsedTime_ %= this->rate_;
        if (this->position_->x < this->limiteMinInX_)
            this->destroyEntity();
    }

    void BugBehaviour::onCollide(const CollisionData &collision)
    {
        if (collision.other.collideGroup == COLLIDE_GROUP_PLAYERS) {
            this->takeDamage(1);
        }
    }

}
