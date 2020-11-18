/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Behaviour system
*/

#pragma once

#include "../components/BehaviourComponent.hpp"
#include "../ABehaviourBase.hpp"
#include "../ecs/system/ASystem.hpp"

namespace rtype {

    /**
     * System responsible for updating behaviour components
     */
    class BehaviourSystem : public ASystem {
      public:
        void update(long elapsedTime)
        {
            this->componentManager_->apply<BehaviourComponent>([&](BehaviourComponent *holder) {
                if (!holder->getEntity()->getVisibility())
                    return;
                std::shared_ptr<ABehaviourBase> script = holder->getBehaviour<ABehaviourBase>();
                script->onUpdate(elapsedTime);
            });
        }
    };

}
