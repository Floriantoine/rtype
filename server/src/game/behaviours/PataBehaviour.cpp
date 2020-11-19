/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Pata behaviour
*/

#include "game/CollideGroups.hpp"
#include "./PataBehaviour.hpp"

namespace rtype::server {
    void PataBehaviour::onUpdate(long elapsedTime)
    {
        if (this->position_ == nullptr) {
            this->position_ = this->getComponent<PositionComponent>();
            this->initInY_ = this->position_->y;
        }
        this->totalElapsedTime_ += elapsedTime;
        long step = this->totalElapsedTime_ / this->rate_;

        this->position_->x -= step * this->stepInX_;
        double sinValue = sin(this->position_->x / this->amplitude_);
        this->position_->y = this->initInY_ + (this->amplitude_ * sinValue);

        if (step > 0)
            this->totalElapsedTime_ %= this->rate_;
        this->sendPosition(this->position_);
        if (this->position_->x < this->limiteMinInX_)
            this->destroyEntity();
    }

    void PataBehaviour::onCollide(const CollisionData &collision)
    {
        if (collision.other.collideGroup == COLLIDE_GROUP_PLAYERS) {
            this->takeDamage(1);
        }
    }

}
