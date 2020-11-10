/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Custom event abstract class
*/

#pragma once

#include "engine/core/events/IEvent.hpp"

namespace rtype
{

/**
 * Custom Event abstract class
 *
 * Use this to create project-specific events
 */
class ACustomEvent: public IEvent
{
    protected:
        virtual ~ACustomEvent() {};

    public:
        virtual const char *GetType() { return "CustomEvent"; }
};

}