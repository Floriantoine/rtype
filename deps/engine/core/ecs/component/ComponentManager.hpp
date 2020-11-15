/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Component manager class
*/

#pragma once

#include "../assert.hpp"
#include "../memory/ObjectPool.hpp"
#include "../types.hpp"
#include "./ComponentBase.hpp"

#include <cassert>
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

namespace rtype {

    class Entity;

    class ComponentManager {
      private:
        std::unordered_map<id_t, std::shared_ptr<IObjectPool>> componentPools_;
        std::unordered_map<id_t, std::unordered_map<id_t, ComponentBase *>> componentLists_;

        bool isComponentTypeRegistered(id_t typeId) const
        {
            return (this->componentPools_.find(typeId) != this->componentPools_.end());
        }

        template <class T>
        bool isComponentTypeRegistered() const
        {
            return this->isComponentTypeRegistered(T::getTypeId());
        }

        template <class T>
        void registerComponentType()
        {
            this->componentPools_.emplace(T::getTypeId(), std::make_shared<ObjectPool<T>>());
            this->componentLists_.emplace(T::getTypeId(), 512);
        }

        std::shared_ptr<IObjectPool> getComponentPool(id_t typeId) const
        {
            auto poolIt = this->componentPools_.find(typeId);
            assert(poolIt != this->componentPools_.end() && "Component type not registered");
            return poolIt->second;
        }

        template <class T>
        std::shared_ptr<ObjectPool<T>> getComponentPool()
        {
            if (this->isComponentTypeRegistered<T>() == false) {
                this->registerComponentType<T>();
            }
            return std::dynamic_pointer_cast<ObjectPool<T>>(this->componentPools_.at(T::getTypeId()));
        }

        std::unordered_map<id_t, ComponentBase *> &getComponentList(id_t typeId)
        {
            auto it = this->componentLists_.find(typeId);
            assert(it != this->componentLists_.end() && "Component type not registered");
            return it->second;
        }

        template <class T>
        std::unordered_map<id_t, ComponentBase *> &getComponentList()
        {
            return this->getComponentList(T::getTypeId());
        }

        bool hasComponent(id_t typeId, id_t entityId)
        {
            if (this->isComponentTypeRegistered(typeId) == false)
                return false;
            auto list = this->getComponentList(typeId);
            return (list.find(entityId) != list.end());
        }

        ComponentBase *getComponent(id_t typeId, id_t entityId)
        {
            if (this->isComponentTypeRegistered(typeId) == false)
                return nullptr;
            auto list = this->getComponentList(typeId);
            auto it = list.find(entityId);
            if (it == list.end())
                return nullptr;
            return it->second;
        }

        void removeComponent(id_t typeId, id_t entityId)
        {
            this->getComponentPool(typeId)->release(this->getComponent(typeId, entityId));
            this->getComponentList(typeId).erase(entityId);
        }

      public:
        ComponentManager() = default;
        ComponentManager(const ComponentManager &) = delete;
        ComponentManager(ComponentManager &&) = delete;
        ~ComponentManager() = default;

        ComponentManager &operator=(const ComponentManager &) = delete;

        template <class T, typename... Args>
        void addComponent(Entity *entity, id_t entityId, Args &&... args)
        {
            assert(this->hasComponent<T>(entityId) == false && "Entity already has component");
            auto pool = this->getComponentPool<T>();
            T *component = static_cast<T *>(pool->get(std::forward<Args>(args)...));
            component->entity_ = entity;
            this->getComponentList<T>()[entityId] = static_cast<ComponentBase *>(component);
        }

        template <class T>
        bool hasComponent(id_t entityId)
        {
            return this->hasComponent(T::getTypeId(), entityId);
        }

        template <class T>
        T *getComponent(id_t entityId)
        {
            STATIC_ASSERT_IS_COMPONENT(T);
            return static_cast<T *>(this->getComponent(T::getTypeId(), entityId));
        }

        template <class T>
        void removeComponent(id_t entityId)
        {
            assert(this->hasComponent<T>(entityId) && "Entity does not have component");
            this->removeComponent(T::getTypeId(), entityId);
        }

        void removeAllComponents(id_t entityId)
        {
            for (auto &list : this->componentLists_) {
                if (list.second.find(entityId) != list.second.end()) {
                    this->removeComponent(list.first, entityId);
                }
            }
        }

        template <class T>
        void apply(std::function<void(T *)> function)
        {
            if (this->isComponentTypeRegistered<T>()) {
                for (const auto &component : this->getComponentList<T>()) {
                    function(static_cast<T *>(component.second));
                }
            }
        }

        template <class T>
        void apply(id_t entityId, std::function<void(T *)> function)
        {
            function(static_cast<T *>(this->getComponent<T>(entityId)));
        }
    };
}