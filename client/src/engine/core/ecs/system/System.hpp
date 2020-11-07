#pragma once

#include <functional>

#include "engine/core/ecs/component/ComponentManager.hpp"
#include "engine/core/ecs/system/ISystem.hpp"

template<class T>
class System: public ISystem
{
    private:
        ComponentManager &componentManager_;
        std::function<void (T *)> updateFunction_;

    public:
        System(std::function<void (T *)> updateFunction)
            : componentManager_ { ComponentManager::getInstance() }
            , updateFunction_ { updateFunction }
        {}

        ~System() override = default;

        void update() override
        {
            this->componentManager_.template apply<T>(this->updateFunction_);
        }

        void update(id_t entityId) override
        {
            this->componentManager_.template apply<T>(entityId, this->updateFunction_);
        }
};
