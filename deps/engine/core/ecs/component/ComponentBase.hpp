/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Component base class
*/

#pragma once

#include "../types.hpp"

namespace rtype {

    class ComponentBase {
        friend class ComponentManager;

      protected:
        id_t entityId_;

        static id_t getNextTypeId()
        {
            static id_t id = 0;
            return id++;
        }

      public:
        id_t getEntityId() const
        {
            return this->entityId_;
        }
    };

}
