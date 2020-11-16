/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Behaviour system
*/

#pragma once

#include "../components/BehaviourComponent.hpp"
#include "../ABehaviour.hpp"
#include "../ecs/system/ASystem.hpp"

namespace rtype {

    /**
     * System responsible for updating script components
     */
    class BehaviourSystem : public ASystem {
      public:
        void update(long elapsedTime)
        {
            this->componentManager_->apply<BehaviourComponent>([&](BehaviourComponent *holder) {
                ABehaviour *script = reinterpret_cast<ABehaviour *>(holder->getBehaviour());
                script->onUpdate(elapsedTime);
            });
        }
    };

}
