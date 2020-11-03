/*
** EPITECH PROJECT, 2020
** client
** File description:
** ComponentManager
*/

#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include "ISystem.hpp"
#include "System.hpp"

class SystemManager
{
private:
    std::unordered_map<std::size_t, std::shared_ptr<ISystem>> systems_;
    ComponentManager *componentManager_;

public:
    SystemManager(ComponentManager *componentManager): componentManager_(componentManager) {};
    ~SystemManager() = default;

    void update()
    {
        for(const auto& system: systems_) {
            system.second->update();
        }
    }

    template<typename T>
    void update()
    {
        std::size_t typeIndex = componentManager_->getComponentTypeId<T>();
        auto it = systems_.find(typeIndex);

        if (it == systems_.end())
            throw std::out_of_range("Cannot update, the system is not created");
        it->second->update();
    }

    template<typename T>
    void update(std::size_t entityId)
    {
        std::size_t typeIndex = componentManager_->getComponentTypeId<T>();
        auto it = systems_.find(typeIndex);

        if (it == systems_.end())
            throw std::out_of_range("Cannot update, the system is not created");
        it->second->update(entityId);
    }

    template<typename T>
    void add(std::function<void (T *)> updateFunction)
    {
        std::size_t typeIndex = componentManager_->getComponentTypeId<T>();

        systems_[typeIndex] = std::make_unique<System<T>>(this->componentManager_, updateFunction);
    }

    template<typename T>
    void del()
    {
        std::size_t typeIndex = componentManager_->getComponentTypeId<T>();

        systems_.erase(typeIndex);
    }
};