#pragma once

#include "engine/core/ecs/component/ComponentBase.hpp"

template<typename T>
class Component: public ComponentBase
{
    public:
        static id_t getTypeId()
        {
            static id_t id = ComponentBase::getNextTypeId();
            return id;
        }
};
