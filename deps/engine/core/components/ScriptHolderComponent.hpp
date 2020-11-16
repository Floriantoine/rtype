/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Script holder component
*/

#pragma once

#include "../ecs/component/Component.hpp"
#include <memory>

namespace rtype {

    class ScriptHolderComponent;

    class IScriptComponent
    {
        friend class ScriptHolderComponent;

      protected:
        IScriptComponent() = default;
        virtual ~IScriptComponent() = default;

      protected:
        ScriptHolderComponent *holder_;
    };

    /*template<class T>
    class AScriptComponent : public IScriptComponent
    {
      protected:
        ScriptHolderComponent *holder;

      public:
        AScriptComponent();
    };*/

    /**
     * The sole purpose of this component is to hold a pointer to an actual 
     * script component
     *
     * This allows for storing scripts of different sizes under the same object 
     * pool (because all ScriptHolder instances will be of the same size)
     */
    class ScriptHolderComponent : public Component<ScriptHolderComponent> {
      private:
        IScriptComponent *script_;

      public:
        ScriptHolderComponent()
        {}
        ScriptHolderComponent(IScriptComponent *script)
            : script_ { script }
        {
            this->script_->holder_ = this;
        }
        ~ScriptHolderComponent() = default;

        ScriptHolderComponent &operator=(const ScriptHolderComponent &other)
        {
            this->script_ = other.script_;
            this->script_->holder_ = this;
            return *this;
        }

        IScriptComponent *getScript()
        {
            return this->script_;
        }
    };

}