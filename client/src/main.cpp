#include <cassert>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <functional>

#include "engine/utils/Singleton.hpp"
#include "engine/core/ecs/types.hpp"
#include "engine/core/ecs/memory/ObjectPool.hpp"

#define ENTITY_MAX 512

#define STATIC_ASSERT_IS_COMPONENT(T) \
    static_assert(std::is_base_of<ComponentBase, T>::value, "T must inherit from ComponentBase");

class ComponentBase
{
    friend class ComponentManager;

    protected:
        id_t entityId;

        static id_t getNextTypeId()
        {
            static id_t id = 0;
            return id++;
        }
};

template<typename T>
class Component: public ComponentBase
{
    public:
        static id_t getTypeId()
        {
            static id_t id = ComponentBase::getNextTypeId();
            return id;
        }
};

class ComponentManager: public Singleton<ComponentManager>
{
    friend class ComponentBase;

    private:
        std::unordered_map<id_t, std::shared_ptr<IObjectPool>> componentPools_;
        std::unordered_map<id_t, std::unordered_map<id_t, ComponentBase *>> componentLists_;

        bool isComponentTypeRegistered(id_t typeId) const
        {
            return (this->componentPools_.find(typeId) != this->componentPools_.end());
        }

        template<class T>
        bool isComponentTypeRegistered() const
        {
            return this->isComponentTypeRegistered(T::getTypeId());
        }

        template<class T>
        void registerComponentType()
        {
            this->componentPools_.emplace(T::getTypeId(), std::make_shared<ObjectPool<T>>());
            this->componentLists_.emplace(T::getTypeId(), ENTITY_MAX);
        }

        std::shared_ptr<IObjectPool> getComponentPool(id_t typeId) const
        {
            auto poolIt = this->componentPools_.find(typeId);
            assert(poolIt != this->componentPools_.end() && "Component type not registered");
            return poolIt->second;
        }

        template<class T>
        std::shared_ptr<ObjectPool<T>> getComponentPool()
        {
            if (this->isComponentTypeRegistered<T>() == false) {
                this->registerComponentType<T>();
            }
            return std::dynamic_pointer_cast<ObjectPool<T>>(this->componentPools_[T::getTypeId()]);
        }

        std::unordered_map<id_t, ComponentBase *> &getComponentList(id_t typeId)
        {
            auto it = this->componentLists_.find(typeId);
            assert(it != this->componentLists_.end() && "Component type not registered");
            return it->second;
        }

        template<class T>
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
            assert(this->hasComponent(typeId, entityId) && "Entity does not have component");
            return this->getComponentList(typeId)[entityId];
        }

        void removeComponent(id_t typeId, id_t entityId)
        {
            this->getComponentPool(typeId)->release(this->getComponent(typeId, entityId));
            this->getComponentList(typeId).erase(entityId);
            std::cout << "Remove component" << std::endl;
        }

    public:
        template<class T, typename ...Args>
        void addComponent(id_t entityId, Args&&...args)
        {
            assert(this->hasComponent<T>(entityId) == false && "Entity already has component");
            auto pool = this->getComponentPool<T>();
            T *component = static_cast<T *>(pool->get(std::forward<Args>(args)...));
            component->entityId = entityId;
            this->getComponentList<T>()[entityId] = static_cast<ComponentBase *>(component);
            std::cout << "Add component" << std::endl;
        }

        template<class T>
        bool hasComponent(id_t entityId)
        {
            return this->hasComponent(T::getTypeId(), entityId);
        }

        template<class T>
        T *getComponent(id_t entityId)
        {
            STATIC_ASSERT_IS_COMPONENT(T);
            return static_cast<T *>(this->getComponent(T::getTypeId(), entityId));
        }

        template<class T>
        void removeComponent(id_t entityId)
        {
            assert(this->hasComponent<T>(entityId) && "Entity does not have component");
            this->removeComponent(T::getTypeId(), entityId);
        }

        void removeAllComponents(id_t entityId)
        {
            for (auto &list: this->componentLists_) {
                if (list.second.find(entityId) != list.second.end()) {
                    this->removeComponent(list.first, entityId);
                }
            }
        }

        template<class T>
        void apply(std::function<void (T *)> function) {
            for (const auto &component: this->getComponentList<T>()) {
                function(static_cast<T *>(component.second));
            }
        }

        template<class T>
        void apply(id_t entityId, std::function<void (T *)> function) {
            function(static_cast<T *>(this->getComponent<T>(entityId)));
        }
};

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

class System
{
    // TODO
};

class PositionComponent: public Component<PositionComponent>
{
    public:
        int x { 0 };
        int y { 0 };

        PositionComponent() = default;
        PositionComponent(int x, int y)
            : x { x }
            , y { y }
        {};
        ~PositionComponent() = default;
};

class GravityComponent: public Component<GravityComponent>
{
    public:
        double g { 9.81 };

        GravityComponent() = default;
        GravityComponent(double g)
            : g { g }
        {};
        ~GravityComponent() = default;
};

int main(void)
{
    ComponentManager &cm = ComponentManager::getInstance();
    {
        Entity player;

        player.addComponent<PositionComponent>(3, 4);
        player.addComponent<GravityComponent>(1);
        auto position = player.getComponent<PositionComponent>();
        std::cout << position->x << ":" << position->y << std::endl;
        std::cout << std::boolalpha << player.hasComponent<PositionComponent>() << std::endl;
    }
    std::cout << std::boolalpha << cm.hasComponent<PositionComponent>(0) << std::endl;
}
