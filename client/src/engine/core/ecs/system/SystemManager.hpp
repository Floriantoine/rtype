/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** System manager class
*/

#pragma once

#include <vector>
#include <memory>
#include <unordered_map>

#include "engine/core/ecs/types.hpp"
#include "engine/core/ecs/assert.hpp"
#include "engine/core/ecs/system/ISystem.hpp"
#include "engine/core/ecs/system/System.hpp"
#include "engine/core/ecs/component/ComponentManager.hpp"

namespace rtype
{

class SystemManager
{
    private:
        ComponentManager &componentManager_;
        std::unordered_map<id_t, std::shared_ptr<ISystem>> systemList_;

    public:
        SystemManager(ComponentManager &componentManager)
            : componentManager_ { componentManager }
        {}
        SystemManager(const SystemManager &) = delete;
        SystemManager(SystemManager &&) = delete;
        ~SystemManager() = default;

        SystemManager &operator=(const SystemManager &) = delete;

        void update()
        {
            for (const auto &system: this->systemList_) {
                system.second->update();
            }
        }

        template<class T>
        void update()
        {
            STATIC_ASSERT_IS_COMPONENT(T);
            auto systemIt = this->systemList_.find(T::getTypeId());
            assert(systemIt != this->systemList_.end() && "No system corresponding to this component type");
            systemIt->second->update();
        }

        template<class T>
        void update(id_t entityId)
        {
            STATIC_ASSERT_IS_COMPONENT(T);
            auto systemIt = this->systemList_.find(T::getTypeId());
            assert(systemIt != this->systemList_.end() && "No system corresponding to this component type");
            systemIt->second->update(entityId);
        }

        template<class T>
        void addSystem(std::function<void (T *)> updateFunction)
        {
            STATIC_ASSERT_IS_COMPONENT(T);
            this->systemList_.emplace(T::getTypeId(), std::make_shared<System<T>>(this->componentManager_, updateFunction));
        }

        template<class T>
        void removeSystem()
        {
            STATIC_ASSERT_IS_COMPONENT(T);
            this->systemList_.erase(T::getTypeId());
        }
};

}