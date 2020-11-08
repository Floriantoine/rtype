#pragma once

#include "engine/core/ecs/types.hpp"

class ISystem
{
public:
    virtual ~ISystem() {};

    virtual void update() = 0;
    virtual void update(id_t) = 0;
};
