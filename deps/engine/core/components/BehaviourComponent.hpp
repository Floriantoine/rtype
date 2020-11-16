/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Behaviour holder component
*/

#pragma once

#include "../ecs/component/Component.hpp"
#include <memory>

namespace rtype {

    class BehaviourComponent;

    class IBehaviour
    {
        friend class BehaviourComponent;

      protected:
        IBehaviour() = default;
        virtual ~IBehaviour() = default;

      protected:
        BehaviourComponent *holder_;
    };

    /**
     * The sole purpose of this component is to hold a pointer to an actual 
     * script component
     *
     * This allows for storing scripts of different sizes under the same object 
     * pool (because all BehaviourComponent instances will be of the same size)
     */
    class BehaviourComponent : public Component<BehaviourComponent> {
      private:
        IBehaviour *script_;

      public:
        BehaviourComponent()
        {}
        BehaviourComponent(IBehaviour *script)
            : script_ { script }
        {
            this->script_->holder_ = this;
        }
        ~BehaviourComponent() = default;

        BehaviourComponent &operator=(const BehaviourComponent &other)
        {
            this->script_ = other.script_;
            this->script_->holder_ = this;
            return *this;
        }

        IBehaviour *getBehaviour()
        {
            return this->script_;
        }
    };

}