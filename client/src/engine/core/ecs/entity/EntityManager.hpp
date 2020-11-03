/*
** EPITECH PROJECT, 2020
** client
** File description:
** ComponentManager
*/

#pragma once

#include <vector>
#include <memory>
#include "Entity.hpp"

class EntityManager
{
private:
    ObjectPool<Entity> entities_;
    ComponentManager *componentManager_;

public:
    EntityManager(ComponentManager *componentManager): componentManager_(componentManager) {};
    ~EntityManager() = default;

    std::size_t getId() {
        static std::size_t id = 0;

        return id++;
    }

    Entity *get()
    {
        void *ptr = entities_.get(componentManager_, getId());

        return static_cast<Entity *>(ptr);
    }

    void release(Entity *ptr)
    {
        entities_.release(ptr);
    }
};