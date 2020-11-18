/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** TextInputBehaviour
*/

#pragma once

#include "SFML/Window/Event.hpp"
#include "game/components/InputComponent.hpp"
#include "game/ABehaviour.hpp"

namespace rtype::client {

    class TextInputBehaviour : public ABehaviour {
      private:
        InputComponent *value { nullptr };
        static std::unordered_map<sf::Keyboard::Key, char> keys_;

        void init_();

      public:
        void onUpdate(long elapsedTime) override;

        void onKeyPressed(const sf::Event &evt) override;
    };

}