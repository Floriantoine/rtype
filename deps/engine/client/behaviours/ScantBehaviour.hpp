/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Scant behaviour
*/

#pragma once

#include "../../core/ABehaviour.hpp"
#include "../../core/components/AnimationComponent.hpp"
#include "../../core/components/MissileComponent.hpp"
#include "../../core/components/PositionComponent.hpp"

#include <cmath>
#include <iostream>

namespace rtype {

    class PataBehaviour : public ABehaviour {
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

        void initComponents_()
        {
            if (this->position_ == nullptr) {
                this->position_ = this->getComponent<PositionComponent>();
                this->initInY_ = this->position_->y;
            }
            if (this->animation_ == nullptr) {
                this->position_ = this->getComponent<AnimationComponent>();
            }
            if (this->missile_ == nullptr) {
                this->missile_ = this->getComponent<MissileComponent>();
            }
        }

      public:
        void onInit() override
        {
        }

        void onUpdate(long elapsedTime) override
        {
            this->initComponents_();

            this->totalElapsedTime_ += elapsedTime;
            this->shootElapsedTime_ += elapsedTime;
            this->shootAnimTime_ += elapsedTime;
            double sinValue = round(sin(this->totalElapsedTime_) * this->accuracy_) / this->accuracy_;
            this->position_->y = this->initInY_ + (this->amplitude_ * sinValue);

            if (this->shootElapsedTime_ > this->shootRate_ && !this->isShooting_) {
                this->shootElapsedTime_ -= this->shootRate_;
                this->isShooting_ = true;
                this->shootAnimTime_ = 0;

                //do the shoot things
                this->animation_->currentFrame = 2;
                
                // and need to create the missile
            }
            if (this->shootAnimTime_ > this->shootAnimRate_ && this->isShooting_) {
                this->isShooting_ = false;

                //stop the shoot things
                this->animation_->currentFrame = 1;
            }
        }

        void onCollide() override
        {
            // static PositionComponent *position = this->getComponent<PositionComponent>();
            // typeCollideComponent;
            // enemy
            // player
            // wall
            // missile
        }
    };
}