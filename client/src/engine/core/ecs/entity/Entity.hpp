#pragma once

#include "engine/core/ecs/types.hpp"
#include "engine/core/ecs/component/ComponentManager.hpp"

class Entity
{
    private:
        ComponentManager &componentManager_;
        static const id_t getNextId()
        {
            static id_t id = 0;
            return id++;
        }

    public:
        const id_t id;

        Entity()
            : componentManager_ { ComponentManager::getInstance() }
            , id { this->getNextId() }
        {}

        ~Entity()
        {
            this->componentManager_.removeAllComponents(this->id);
        }

        template<class T, typename ...Args>
        void addComponent(Args&&...args)
        {
            STATIC_ASSERT_IS_COMPONENT(T);
            this->componentManager_.addComponent<T>(this->id, std::forward<Args>(args)...);
        }

        template<class T>
        bool hasComponent()
        {
            STATIC_ASSERT_IS_COMPONENT(T);
            return this->componentManager_.hasComponent<T>(this->id);
        }

        template<class T>
        T *getComponent()
        {
            STATIC_ASSERT_IS_COMPONENT(T);
            return this->componentManager_.getComponent<T>(this->id);
        }

        template<class T>
        void removeComponent()
        {
            STATIC_ASSERT_IS_COMPONENT(T);
            this->componentManager_.removeComponent<T>(this->id);
        }
};

