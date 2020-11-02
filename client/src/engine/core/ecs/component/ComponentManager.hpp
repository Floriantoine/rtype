/*
** EPITECH PROJECT, 2020
** client
** File description:
** ComponentManager
*/

#pragma once

#include <vector>
#include <src/engine/core/ecs/memory/ObjectPool.hpp>
#include "IComponent.hpp"

const int ENTITY_MAX = 3000;

class ComponentManager
{
private:
    std::vector<std::vector<IComponent *>> componentsType_;
    std::vector<std::shared_ptr<IObjectPool>> componentsObjectPools_;

public:
    ComponentManager() = default;
    ~ComponentManager() = default;

    static std::size_t getId()
    {
        static std::size_t id = 0;

        return id++;
    }

    template<typename T>
    std::size_t getComponentTypeId()
    {
        static std::size_t typeId = getId();

        return typeId;
    }

    template<typename T>
    void addComponentType()
    {
        getComponentTypeId<T>();
        componentsType_.emplace_back(ENTITY_MAX, nullptr);
        componentsObjectPools_.push_back(std::make_unique<ObjectPool<T, ENTITY_MAX>>());
    }

    template<typename T, typename ...Args>
    T *get(std::size_t entityId, Args&&...args)
    {
        std::size_t typeId = getComponentTypeId<T>();
        T *component = static_cast<T *>(this->componentsType_[typeId][entityId]);

        if (component == nullptr) {
            component = static_cast<T *>(componentsObjectPools_[typeId]->get(std::forward<Args>(args)...));
            this->componentsType_[typeId][entityId] = component;
        }
        return component;
    }

    template<typename T>
    void release(std::size_t entityId)
    {
        std::size_t typeId = getComponentTypeId<T>();

        componentsObjectPools_[typeId]->release(this->componentsType_[typeId][entityId]);
        this->componentsType_[typeId][entityId] = nullptr;
    }

    template<typename T>
    void apply(std::function<void (T *)> function)
    {
        std::size_t typeId = getComponentTypeId<T>();

        for (auto &component: this->componentsType_[typeId]) {
            function(static_cast<T *>(component));
        }
    }

    void delAll(std::size_t entityId)
    {
        std::size_t index = 0;

        for (auto &components: this->componentsType_) {
            componentsObjectPools_[index]->release(components[entityId]);
            components[entityId] = nullptr;
            ++index;
        }
    }
};