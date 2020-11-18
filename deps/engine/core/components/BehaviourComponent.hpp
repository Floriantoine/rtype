/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Behaviour holder component
*/

#pragma once

#include "../ecs/component/Component.hpp"
#include "core/ecs/assert.hpp"

#include <memory>

namespace rtype {

    class BehaviourComponent;

    class IBehaviour {
        friend class BehaviourComponent;

      protected:
        IBehaviour() = default;
        virtual ~IBehaviour() = default;

      protected:
        BehaviourComponent *holder_ { nullptr };
    };

    /**
     * The sole purpose of this component is to hold a pointer to an actual 
     * behaviour
     *
     * This allows for storing behaviours of different sizes under the same object 
     * pool (because all BehaviourComponent instances will be of the same size)
     */
    class BehaviourComponent : public Component<BehaviourComponent> {
      private:
        std::shared_ptr<IBehaviour> behaviour_;

      public:
        BehaviourComponent() = default;
        BehaviourComponent(std::shared_ptr<IBehaviour> &&behaviour)
            : behaviour_(std::move(behaviour))
        {
            this->behaviour_->holder_ = this;
        }
        ~BehaviourComponent() = default;

        BehaviourComponent &operator=(const BehaviourComponent &other)
        {
            this->behaviour_ = other.behaviour_;
            this->behaviour_->holder_ = this;
            return *this;
        }

        std::shared_ptr<IBehaviour> getBehaviour() const
        {
            return this->behaviour_;
        }

        template <class T>
        std::shared_ptr<T> getBehaviour() const
        {
            STATIC_ASSERT_IS_BASE_OF(IBehaviour, T);
            return std::dynamic_pointer_cast<T>(this->behaviour_);
        }
    };
}
