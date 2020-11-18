/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Pata behaviour
*/

#pragma once

#include "core/ABehaviour.hpp"
#include "core/components/PositionComponent.hpp"

namespace rtype::client {
    class CameraBehaviour : public ABehaviour {
      private:
        PositionComponent *position_ = nullptr;

        float speed_ = 50.0;

        void init_();

      public:
        void onUpdate(long elapsedTime) override;
    };

}
