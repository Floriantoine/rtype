/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** HealthSystem
*/

#pragma once

#include "../ABehaviourBase.hpp"
#include "../components/BehaviourComponent.hpp"
#include "../components/HealthComponent.hpp"
#include "../ecs/system/ASystem.hpp"

namespace rtype {

    class HealthSystem : public ASystem {
      public:
        HealthSystem()
            : ASystem() {};
        ~HealthSystem() = default;

        void update(long elapsedTime) override
        {
            this->componentManager_->apply<HealthComponent>([&](HealthComponent *component) {
                if (component->health <= 0) {
                    BehaviourComponent *behaviour = component->getEntity()->getComponent<BehaviourComponent>();
                    if (behaviour != nullptr) {
                        behaviour->getBehaviour<ABehaviourBase>()->onDestroy();
                    }
                    this->destroyEntity(component->getEntity());
                }
            });
        };

      private:
        void destroyEntity(Entity *entity) const
        {
            entity->getEntityManager()->destroyEntity(entity->getId());
        }
    };
}
