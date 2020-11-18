/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Behaviour abstract class
*/

#pragma once

#include "engine/core/ABehaviourBase.hpp"

namespace sf {
    class Event;
}

namespace rtype::client {

    /**
     * Behaviour abstract class
     *
     * Behaviours are entity-specific behaviours
     * Behaviours must inherit from this class to be triggered by the default 
     * systems
     */
    class ABehaviour : public ABehaviourBase {
      public:
        /**
         * Method called when the mouse cursor moves on screen
         */
        virtual void onMouseMove(const sf::Event &) {};

        /**
         * Method called when the mouse cursor hovers the entity's collide box
         */
        virtual void onMouseHover(const sf::Event &) {};

        /**
         * Method called when the mouse button is pressed over the entity's collide box
         */
        virtual void onMouseClick(const sf::Event &) {};
        
        /**
         * Method called when a keyboard key is pressed
         */
        virtual void onKeyPressed(const sf::Event &) {};

        /**
         * Method called when a keyboard key is released
         */
        virtual void onKeyReleased(const sf::Event &) {};

        /**
         * Method called when a mouse button is pressed
         */
        virtual void onMouseButtonPressed(const sf::Event &) {};

        /**
         * Method called when a mouse button is released
         */
        virtual void onMouseButtonReleased(const sf::Event &) {};
    };
}
