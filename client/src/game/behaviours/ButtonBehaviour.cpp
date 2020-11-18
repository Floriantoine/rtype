/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** ButtonBehaviour
*/

#include "ButtonBehaviour.hpp"

#include <iostream>

namespace rtype::client {

void ButtonBehaviour::onUpdate(long elapsedTime)
{
}

void ButtonBehaviour::onMouseMove(const sf::Event &evt)
{
    this->isHovered_ = false;
}

void ButtonBehaviour::onMouseHover(const sf::Event &evt)
{
    this->isHovered_ = true;
}

void ButtonBehaviour::onMouseClick(const sf::Event &evt)
{
    this->isClicked_ = true;
}

void ButtonBehaviour::onMouseButtonReleased(const sf::Event &evt)
{
    this->isClicked_ = false;
}

}