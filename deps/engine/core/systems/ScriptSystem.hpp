/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** ScriptSystem
*/

#pragma once

#include "../components/AScriptComponent.hpp"
#include "../ecs/system/ASystem.hpp"

namespace rtype {

    /**
     * System responsible for updating script components
     */
    class ScriptSystem : public ASystem {
      public:
        void update(long elapsedTime)
        {
            this->componentManager_->apply<AScriptComponent>([](AScriptComponent *component) {
                component->onUpdate();
            });
        }
    };

}
