/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Pata behaviour
*/

#pragma once

#include "../../core/ABehaviour.hpp"
#include "../../core/components/CameraComponent.hpp"
#include "../../core/components/PositionComponent.hpp"

namespace rtype {

    class CameraBehaviour : public ABehaviour {
      private:
        PositionComponent *position_ = nullptr;

        float speed_ = 50.0;

        void init_()
        {
            if (this->position_ == nullptr) {
                this->position_ = this->getComponent<PositionComponent>();
            }
        }

      public:
        void onUpdate(long elapsedTime) override
        {
            this->init_();

            if (this->position_ != nullptr) {
                this->position_->x += (this->speed_ * elapsedTime) / 1000.0;
            }
        }
    };

}
