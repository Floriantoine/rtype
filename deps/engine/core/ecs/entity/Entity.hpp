/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Entity class
*/

#pragma once

#include "../component/ComponentManager.hpp"
#include "../types.hpp"

namespace rtype {
    class EntityManager;

    class Entity {
        friend class EntityManager;

      private:
        ComponentManager *componentManager_;
        EntityManager *entityManager_;

        static const id_t getNextId()
        {
            static id_t id = 0;
            return id++;
        }

        id_t id_;

      public:
        Entity()
            : id_ { this->getNextId() }
        { }
        ~Entity() = default;

        Entity &operator=(const Entity &other)
        {
            this->id_ = other.getId();
            return *this;
        }

        id_t getId() const
        {
            return this->id_;
        }

        EntityManager *getEntityManager() const
        {
            return this->entityManager_;
        }

        template <class T, typename... Args>
        void addComponent(Args &&... args)
        {
            STATIC_ASSERT_IS_COMPONENT(T);
            this->componentManager_->addComponent<T>(this, this->getId(), std::forward<Args>(args)...);
        }

        template <class T>
        bool hasComponent()
        {
            STATIC_ASSERT_IS_COMPONENT(T);
            return this->componentManager_->hasComponent<T>(this->getId());
        }

        template <class T>
        T *getComponent()
        {
            STATIC_ASSERT_IS_COMPONENT(T);
            return this->componentManager_->getComponent<T>(this->getId());
        }

        template <class T>
        void removeComponent()
        {
            STATIC_ASSERT_IS_COMPONENT(T);
            this->componentManager_->removeComponent<T>(this->getId());
        }
    };

}
