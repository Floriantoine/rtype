/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** CreateButtonBehaviour
*/

#pragma once

#include "game/behaviours/NavButtonBehaviour.hpp"

namespace rtype::client {

    class CreateButtonBehaviour : public NavButtonBehaviour {
      public:
        void onMouseClick(const sf::Event &evt) override;
    };

}