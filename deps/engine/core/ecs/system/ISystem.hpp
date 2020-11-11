/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** System interface
*/

#pragma once

#include "engine/core/ecs/types.hpp"

namespace rtype
{

class ISystem
{
public:
    virtual ~ISystem() {};

    virtual void update() = 0;
    virtual void update(id_t) = 0;
};

}