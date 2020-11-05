#pragma once

#include "engine/core/ecs/component/ComponentManager.hpp"

class Entity
{
private:
    ComponentManager *componentManager_;
    std::size_t entityId_;

public:
    Entity() = default;
    Entity(ComponentManager *componentManager, std::size_t entityId):
            componentManager_(componentManager), entityId_(entityId) {};
    ~Entity() = default;

    std::size_t getId()
    {
        return this->entityId_;
    }

    template<typename T>
    T *GetComponent()
    {
        return this->componentManager_->get<T>(this->entityId_);
    }

    template<typename T, typename ...Args>
    T *AddComponent(Args&&... args)
    {
        return this->componentManager_->get<T>(this->entityId_, std::forward<Args>(args)...);
    }

    template<typename T>
    T *DelComponent()
    {
        return this->componentManager_->release<T>(this->entityId_);
    }
};
