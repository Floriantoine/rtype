/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Pata behaviour
*/

#include "CameraBehaviour.hpp"

namespace rtype::client {
    void CameraBehaviour::init_()
    {
        if (this->position_ == nullptr) {
            this->position_ = this->getComponent<PositionComponent>();
        }
    }

    void CameraBehaviour::onUpdate(long elapsedTime)
    {
        this->init_();

        if (this->position_ != nullptr) {
            this->position_->x += (this->speed_ * elapsedTime) / 1000.0;
        }
    }
}
