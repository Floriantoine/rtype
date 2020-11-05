#pragma once

#include "engine/core/ecs/component/ComponentManager.hpp"

class ISystem
{
public:
    virtual ~ISystem() {};

    virtual void update() = 0;
    virtual void update(std::size_t) = 0;
};
