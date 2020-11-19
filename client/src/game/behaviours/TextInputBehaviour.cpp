/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** TextInputBehaviour
*/

#include "TextInputBehaviour.hpp"

#include "game/components/TextComponent.hpp"

#include <iostream>

namespace rtype::client {

    const std::unordered_map<sf::Keyboard::Key, char> TextInputBehaviour::keys_ = {
        { sf::Keyboard::A, 'A' },
        { sf::Keyboard::B, 'B' },
        { sf::Keyboard::C, 'C' },
        { sf::Keyboard::D, 'D' },
        { sf::Keyboard::E, 'E' },
        { sf::Keyboard::F, 'F' },
        { sf::Keyboard::G, 'G' },
        { sf::Keyboard::H, 'H' },
        { sf::Keyboard::I, 'I' },
        { sf::Keyboard::J, 'J' },
        { sf::Keyboard::K, 'K' },
        { sf::Keyboard::L, 'L' },
        { sf::Keyboard::M, 'M' },
        { sf::Keyboard::N, 'N' },
        { sf::Keyboard::O, 'O' },
        { sf::Keyboard::P, 'P' },
        { sf::Keyboard::Q, 'Q' },
        { sf::Keyboard::R, 'R' },
        { sf::Keyboard::S, 'S' },
        { sf::Keyboard::T, 'T' },
        { sf::Keyboard::U, 'U' },
        { sf::Keyboard::V, 'V' },
        { sf::Keyboard::W, 'W' },
        { sf::Keyboard::X, 'X' },
        { sf::Keyboard::Y, 'Y' },
        { sf::Keyboard::Z, 'Z' }
    };

    void TextInputBehaviour::init_()
    {
        if (this->value == nullptr) {
            this->value = this->getEntity()->getComponent<InputComponent>();
        }
    }

    void TextInputBehaviour::onUpdate(long elapsedTime)
    {
        this->init_();
    }

    void TextInputBehaviour::onKeyPressed(const sf::Event &evt)
    {
        if (this->value == nullptr) {
            std::cerr << "warn: no input component associated to input behaviour" << std::endl;
            return;
        }
        if (evt.key.code == sf::Keyboard::BackSpace) {
            if (this->value->string.size() > 0) {
                this->value->string.pop_back();
                this->onChange(this->value->string);
            }
            return;
        }
        if (this->value->max != 0 && this->value->string.size() >= this->value->max)
            return;
        const auto &it = this->keys_.find(evt.key.code);
        if (it == this->keys_.end())
            return;
        this->value->string.push_back(it->second);
        this->onChange(this->value->string);
    }

    void TextInputBehaviour::onChange(const std::string &value)
    {
    }

}