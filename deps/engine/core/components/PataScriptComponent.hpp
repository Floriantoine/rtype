/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Player Script Component
*/

#pragma once

#include "./AScriptComponent.hpp"
#include "./PositionComponent.hpp"

#include <cmath>
#include <iostream>

namespace rtype {

    class PataScriptComponent : public AScriptComponent {
      private:
        std::size_t amplitude_ = 15;
        int accuracy_ = 100;

        std::size_t stepInX_ = 1;

        long totalElapsedTime_ = 0;
        long rate_ = 16;

        int limiteMinInX_ = 0;

        PositionComponent *position_ = nullptr;
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
            double sinValue = sin(this->position_->x / this->amplitude_);
            this->position_->y = this->initInY_ + (this->amplitude_ * sinValue);

            if (step)
                this->totalElapsedTime_ %= this->rate_;
            if (this->position_->x < this->limiteMinInX_)
                this->destroyEntity();
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
