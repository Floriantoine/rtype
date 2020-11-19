/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** NavButtonBehaviour
*/

#pragma once

#include "./ButtonBehaviour.hpp"
#include "game/components/NavDirectionComponent.hpp"

namespace rtype::client {

    class NavButtonBehaviour : public ButtonBehaviour {
      private:
        NavDirectionComponent *direction_;

        void init_();

      public:
        void onUpdate(long elapsedTime) override;

        void onMouseMove(const sf::Event &evt) override;

        void onMouseHover(const sf::Event &evt) override;
        
        void onMouseClick(const sf::Event &evt) override;

        void onMouseButtonReleased(const sf::Event &evt) override;
    };

}