#pragma once

#include "engine/core/ecs/types.hpp"

class ComponentBase
{
    friend class ComponentManager;

    protected:
        id_t entityId;

        static id_t getNextTypeId()
        {
            static id_t id = 0;
            return id++;
        }

    public:
        id_t getEntityId() const
        {
            return entityId;
        }
};
