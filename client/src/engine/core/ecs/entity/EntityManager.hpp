/*
** EPITECH PROJECT, 2020
** client
** File description:
** ComponentManager
*/

#pragma once

#include <vector>
#include <memory>

#include "engine/utils/Singleton.hpp"
#include "engine/core/ecs/component/ComponentManager.hpp"
#include "engine/core/ecs/entity/Entity.hpp"

class EntityManager: public Singleton<EntityManager>
{
    friend Entity;

    private:
        ObjectPool<Entity> entityPool_;
        ComponentManager &componentManager_;

    public:
        EntityManager()
            : componentManager_ { ComponentManager::getInstance() }
        {}

        ~EntityManager() = default;

        std::shared_ptr<Entity> createEntity()
        {
            Entity *entity = static_cast<Entity *>(this->entityPool_.get());
            return std::shared_ptr<Entity>(entity, [](Entity *self) {
                EntityManager::getInstance().destroyEntity(self);
            });
        }

        void destroyEntity(Entity *entity)
        {
            this->componentManager_.removeAllComponents(entity->getId());
            this->entityPool_.release(entity);
        }
};
