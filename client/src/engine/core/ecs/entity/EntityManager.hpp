/*
** EPITECH PROJECT, 2020
** client
** File description:
** ComponentManager
*/

#pragma once

#include <vector>
#include <memory>

#include "engine/core/ecs/entity/Entity.hpp"

class EntityManager
{
private:
    ObjectPool<Entity> entityPool_;
    ComponentManager *componentManager_;

public:
    EntityManager(ComponentManager *componentManager)
        : componentManager_ { componentManager }
    {};
    ~EntityManager() = default;

    Entity *get()
    {
        void *entity = entityPool_.get(componentManager_);
        return static_cast<Entity *>(entity);
    }

    void release(Entity *ptr)
    {
        entityPool_.release(ptr);
    }
};
