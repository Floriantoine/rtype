/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** ButtonBehaviour
*/

#pragma once

#include "game/ABehaviour.hpp"

namespace rtype::client {
    class ButtonBehaviour : public ABehaviour {
      private:
        float blinkRate_ = 50.0;

        void init_();

      public:
        void onUpdate(long elapsedTime) override;
    };

}