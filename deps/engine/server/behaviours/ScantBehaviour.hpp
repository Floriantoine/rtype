/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Scant behaviour
*/

#pragma once

#include "../../core/ABehaviour.hpp"
#include "../../core/components/MissileComponent.hpp"
#include "../../core/components/PositionComponent.hpp"

#include <cmath>
#include <iostream>

namespace rtype::server {

    class ScantBehaviour : public ABehaviour {
      private:
        std::size_t amplitude_ = 400;
        int accuracy_ = 1;

        std::size_t stepInX_ = 1;

        long shootAnimElapsedTime_ = 0;
        long totalElapsedTime_ = 0;

        bool isShooting_ = false;
        int shootAnimRate_ = 200;
        int shootRate_ = 1500;

        PositionComponent *position_ = nullptr;
        MissileComponent *missile_ = nullptr;
        std::size_t initInY_ = 0;

        void initComponents_()
        {
            if (this->position_ == nullptr) {
                this->position_ = this->getComponent<PositionComponent>();
                this->initInY_ = this->position_->y;
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
            this->shootAnimRate_ += elapsedTime;
            double sinValue = round(sin(this->totalElapsedTime_) * this->accuracy_) / this->accuracy_;
            this->position_->y = this->initInY_ + (this->amplitude_ * sinValue);
        }

        void onCollide(const CollisionData &collision) override
        {
        }
    };
}