/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Collide system
*/

#pragma once

#include "../ABehaviourBase.hpp"
#include "../components/BehaviourComponent.hpp"
#include "../components/CollideBoxComponent.hpp"
#include "../components/CollideGroupComponent.hpp"
#include "../components/PositionComponent.hpp"
#include "../ecs/system/ASystem.hpp"
#include "../physics/CollisionChecker.hpp"
#include "../physics/CollisionData.hpp"

#include <iostream>

namespace rtype {

    /**
     * System responsible for checking collisions between entities collide boxes
     */
    class CollisionSystem : public ASystem {
      public:
        void update(long elapsedTime) override
        {
            this->componentManager_->apply<CollideBoxComponent>(
                [this](CollideBoxComponent *collideBox, id_t id, const std::unordered_map<id_t, ComponentBase *> &list) {
                    if (!collideBox->getEntity()->getVisibility())
                        return;
                    BehaviourComponent *behaviourComponent = collideBox->getEntity()->getComponent<BehaviourComponent>();
                    if (behaviourComponent == nullptr)
                        return;
                    std::shared_ptr<ABehaviourBase> behaviour = behaviourComponent->getBehaviour<ABehaviourBase>();
                    ColliderData selfData = CollisionSystem::getColliderData(collideBox);

                    for (auto &it : list) {
                        if (it.first == id || !it.second->getEntity()->getVisibility())
                            continue;
                        CollideBoxComponent *otherCollideBox = reinterpret_cast<CollideBoxComponent *>(it.second);
                        ColliderData otherData = CollisionSystem::getColliderData(otherCollideBox);
                        if (CollisionChecker::collides<float>(selfData.relativeCollideBox, otherData.relativeCollideBox) == false)
                            continue;
                        behaviour->onCollide(CollisionData(selfData, otherData));
                    }
                });
        }

      private:
        static Rect<float> getRelativeCollideBox(CollideBoxComponent *collideBox)
        {
            Vector2<float> position;

            if (PositionComponent *positionComponent = collideBox->getEntity()->getComponent<PositionComponent>()) {
                position.x = positionComponent->x;
                position.y = positionComponent->y;
            }
            return collideBox->box + position;
        }

        static ColliderData getColliderData(CollideBoxComponent *collideBox)
        {
            Entity *entity = collideBox->getEntity();
            CollideGroupComponent *groupComponent = entity->getComponent<CollideGroupComponent>();

            int group = groupComponent != nullptr
                ? groupComponent->group
                : -1;
            return ColliderData(entity, group, CollisionSystem::getRelativeCollideBox(collideBox));
        }
    };

}
