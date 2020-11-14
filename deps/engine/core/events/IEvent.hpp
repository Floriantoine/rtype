/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Event interface
*/

#pragma once

#include <string>

namespace rtype {

    /**
     * Event interface
     *
     * Stores data related to an event
     */
    class IEvent {
      protected:
        virtual ~IEvent() { }

      public:
        virtual const char *GetType() = 0;
    };
}