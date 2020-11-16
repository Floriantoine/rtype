/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** System class
*/

#pragma once

#include "engine/core/ecs/component/ComponentManager.hpp"
#include "../types.hpp"

namespace rtype {

    class ASystem {
        friend class SystemManager;

      public:
        enum system_group_e {
            UNKNOWN_SYSTEM_GROUP = -1,
            RENDER_SYSTEM_GROUP
        };

      private:
        system_group_e group_;

      protected:
        ComponentManager *componentManager_;

        ASystem(system_group_e group = UNKNOWN_SYSTEM_GROUP)
            : group_ { group }
        { }
        ~ASystem() = default;

      public:
        virtual void update(long elapsedTime) = 0;

        system_group_e getGroup()
        {
            return this->group_;
        }
    };

}
