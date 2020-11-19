/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** NavButtonBehaviour
*/

#include "NavButtonBehaviour.hpp"
#include "game/Game.hpp"

#include <iostream>

namespace rtype::client {

void NavButtonBehaviour::init_()
{
    if (this->direction_ == nullptr) {
        this->direction_ = this->getComponent<NavDirectionComponent>();
    }
}

void NavButtonBehaviour::onUpdate(long elapsedTime)
{
    ButtonBehaviour::onUpdate(elapsedTime);
    this->init_();
}

void NavButtonBehaviour::onMouseMove(const sf::Event &evt)
{
    ButtonBehaviour::onMouseMove(evt);
}

void NavButtonBehaviour::onMouseHover(const sf::Event &evt)
{
    ButtonBehaviour::onMouseHover(evt);
}

void NavButtonBehaviour::onMouseClick(const sf::Event &evt)
{
    ButtonBehaviour::onMouseClick(evt);
    if (this->direction_ == nullptr) {
        std::cerr << "warn: no direction component associated to a nav button. Ignoring." << std::endl;
        return;
    }
    Game::getInstance().goToScene(this->direction_->direction);
}

void NavButtonBehaviour::onMouseButtonReleased(const sf::Event &evt)
{
    ButtonBehaviour::onMouseButtonReleased(evt);
}

}