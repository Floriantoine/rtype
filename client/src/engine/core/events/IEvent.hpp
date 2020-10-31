#pragma once

#include <string>

/**
 * Event interface
 *
 * Stores data related to an event
 */
class IEvent
{
    protected:
        virtual ~IEvent() {}

    public:
        virtual const char *GetType() = 0;
};
