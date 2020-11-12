/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Object pool interface
*/

#pragma once

namespace rtype {

    /**
     * ObjectPool interface, mainly used to store ObjectPool of different types 
     * together
     */
    class IObjectPool {
      protected:
        virtual ~IObjectPool() = default;

      public:
        virtual void *get() = 0;
        virtual void release(void *) = 0;
    };

}