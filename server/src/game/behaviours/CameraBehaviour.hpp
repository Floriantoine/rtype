/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Pata behaviour
*/

#pragma once

#include "engine/core/ABehaviourBase.hpp"
#include "engine/core/components/PositionComponent.hpp"

namespace rtype::server {

    class CameraBehaviour : public ABehaviourBase {
      private:
        PositionComponent *position_ = nullptr;

        float speed_ = 50.0;

        void init_();

      public:
        void onUpdate(long elapsedTime) override;
    };

}
