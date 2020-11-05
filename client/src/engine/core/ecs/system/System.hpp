#pragma once

#include <functional>

#include "engine/core/ecs/system/ISystem.hpp"

template<class T>
class System : public ISystem
{
private:
    ComponentManager *componentManager_;
    std::function<void (T *)> updateFunction_;
public:
    System(ComponentManager *componentManager, std::function<void (T *)> updateFunction):
    componentManager_(componentManager), updateFunction_(updateFunction) {};
    ~System() override = default;

    void update() override
    {
        componentManager_->apply<T>(updateFunction_);
    };

    void update(std::size_t entityId) override
    {
        componentManager_->apply<T>(entityId, updateFunction_);
    };
};
