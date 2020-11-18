/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Entity manager class
*/

#pragma once

#include "./Entity.hpp"

#include <memory>
#include <vector>

namespace rtype {

    class EntityManager {
      private:
        ObjectPool<Entity> entityPool_;
        ComponentManager &componentManager_;

        std::unordered_map<id_t, std::shared_ptr<Entity>> entities_;

        void destroyEntity(Entity *entity)
        {
            this->componentManager_.removeAllComponents(entity->getId());
            this->entityPool_.release(entity);
        }

      public:
        EntityManager(ComponentManager &componentManager)
            : componentManager_ { componentManager }
        { }
        EntityManager(const EntityManager &) = delete;
        EntityManager(EntityManager &&) = delete;
        ~EntityManager() = default;

        EntityManager &operator=(const EntityManager &) = delete;

        std::shared_ptr<Entity> createEntity()
        {
            Entity *ptr = static_cast<Entity *>(this->entityPool_.get());
            ptr->componentManager_ = &this->componentManager_;
            ptr->entityManager_ = this;
            this->entities_.emplace(ptr->getId(), std::shared_ptr<Entity>(ptr, [this](Entity *self) {
                this->destroyEntity(self);
            }));
            return this->entities_[ptr->getId()];
        }

        std::shared_ptr<Entity> getEntity(id_t id)
        {
            const auto &it = this->entities_.find(id);

            if (it != this->entities_.end()) {
                return it->second;
            }
            return std::shared_ptr<Entity>(nullptr);
        }

        void destroyEntity(id_t id)
        {
            std::shared_ptr<Entity> entity = this->getEntity(id);
            if (entity.get() != nullptr) {
                this->destroyEntity(entity.get());
            }
        }
    };

}