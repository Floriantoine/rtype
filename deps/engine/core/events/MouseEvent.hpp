/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Mouse event class
*/

#pragma once

#include "./ACustomEvent.hpp"

namespace rtype {

    /**
     * Custom Event abstract class
     *
     * Use this to create project-specific events
     */
    class MouseEvent : public ACustomEvent {
      public:
        MouseEvent() = default;
        ~MouseEvent() = default;

        const char *GetType()
        {
            return "MouseEvent";
        }
    };

}