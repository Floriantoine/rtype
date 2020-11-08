#pragma once

#include "ACustomEvent.hpp"

/**
 * Custom Event abstract class
 *
 * Use this to create project-specific events
 */
class MouseEvent: public ACustomEvent
{
    public:
        MouseEvent() = default;
        ~MouseEvent() = default;

        const char *GetType() { return "MouseEvent"; }
};
