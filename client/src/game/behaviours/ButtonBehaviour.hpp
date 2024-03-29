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
        bool isHovered_ { false };
        bool isClicked_ { false };

      protected:
        bool isHovered() { return this->isHovered_; }
        bool isClicked() { return this->isClicked_; }

      public:
        void onUpdate(long elapsedTime) override;

        void onMouseMove(const sf::Event &evt) override;

        void onMouseHover(const sf::Event &evt) override;
        
        void onMouseClick(const sf::Event &evt) override;

        void onMouseButtonReleased(const sf::Event &evt) override;
    };

}