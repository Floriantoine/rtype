#pragma once

#include "IEvent.hpp"

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
