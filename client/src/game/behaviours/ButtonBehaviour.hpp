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
        float isHovered_ { false };
        float isClicked_ { false };

        void init_();

      public:
        void onUpdate(long elapsedTime) override;

        void onMouseMove(const sf::Event &evt) override;

        void onMouseHover(const sf::Event &evt) override;
        
        void onMouseClick(const sf::Event &evt) override;

        void onMouseButtonReleased(const sf::Event &evt) override;
    };

}