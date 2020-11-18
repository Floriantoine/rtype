/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Scant behaviour
*/

#include "./ScantBehaviour.hpp"

namespace rtype::server {

    void ScantBehaviour::initComponents_()
    {
        // if (this->position_ == nullptr) {
        //     this->position_ = this->getComponent<PositionComponent>();
        //     this->initInY_ = this->position_->y;
        // }
        // if (this->animation_ == nullptr) {
        //     this->position_ = this->getComponent<AnimationComponent>();
        // }
        // if (this->missile_ == nullptr) {
        //     this->missile_ = this->getComponent<MissileComponent>();
        // }
    }

    void ScantBehaviour::onUpdate(long elapsedTime)
    {
        // this->initComponents_();

        // this->totalElapsedTime_ += elapsedTime;
        // this->shootElapsedTime_ += elapsedTime;
        // this->shootAnimTime_ += elapsedTime;
        // double sinValue = round(sin(this->totalElapsedTime_) * this->accuracy_) / this->accuracy_;
        // this->position_->y = this->initInY_ + (this->amplitude_ * sinValue);

        // if (this->shootElapsedTime_ > this->shootRate_ && !this->isShooting_) {
        //     this->shootElapsedTime_ -= this->shootRate_;
        //     this->isShooting_ = true;
        //     this->shootAnimTime_ = 0;

        //     //do the shoot things
        //     this->animation_->currentFrame = 2;

        //     // and need to create the missile
        // }
        // if (this->shootAnimTime_ > this->shootAnimRate_ && this->isShooting_) {
        //     this->isShooting_ = false;

        //     //stop the shoot things
        //     this->animation_->currentFrame = 1;
        // }
    }

    void ScantBehaviour::onCollide(const CollisionData &collision)
    {
    }
}