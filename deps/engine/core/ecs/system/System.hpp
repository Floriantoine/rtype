/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** System class
*/

#pragma once

#include "../component/ComponentManager.hpp"
#include "./ISystem.hpp"

#include <functional>

namespace rtype {

    template <class T>
    class System : public ISystem {
      private:
        ComponentManager &componentManager_;
        std::function<void(T *)> updateFunction_;

      public:
        System(ComponentManager &componentManager, std::function<void(T *)> updateFunction)
            : componentManager_ { componentManager }
            , updateFunction_ { updateFunction }
        { }
        System(const System &) = delete;
        System(System &&) = delete;
        ~System() override = default;

        System &operator=(const System &) = delete;

        void update() override
        {
            this->componentManager_.template apply<T>(this->updateFunction_);
        }

        void update(id_t entityId) override
        {
            this->componentManager_.template apply<T>(entityId, this->updateFunction_);
        }
    };

}