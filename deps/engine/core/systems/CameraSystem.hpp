/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Camera system
*/

#pragma once

#include "../Rect.hpp"
#include "../components/CameraComponent.hpp"
#include "../components/SpriteComponent.hpp"
#include "../ecs/system/ASystem.hpp"
#include "../physics/CollisionChecker.hpp"

namespace rtype {

    /**
     * System responsible for updating behaviour components
     */
    class CameraSystem : public ASystem {
      public:
        void update(long elapsedTime)
        {
            Entity *cameraEntity = this->getCamera();

            if (cameraEntity == nullptr)
                return;
            CameraComponent *camera = cameraEntity->getComponent<CameraComponent>();
            Rect<float> cameraRect = this->getRelativeBounds(camera);

            this->componentManager_->apply<SpriteComponent>([&](SpriteComponent *sprite) {
                Rect<float> spriteRect = this->getRelativeBounds(sprite);

                BehaviourComponent *behaviourComponent = sprite->getEntity()->getComponent<BehaviourComponent>();
                std::shared_ptr<ABehaviour> behaviour;
                if (behaviourComponent != nullptr)
                    behaviour = behaviourComponent->getBehaviour<ABehaviour>();

                bool collides = CollisionChecker::collides<float>(cameraRect, spriteRect);
                if (collides && sprite->getEntity()->getVisibility() == false) {
                    sprite->getEntity()->setVisibility(true);
                    if (behaviour)
                        behaviour->onViewEnter();
                } else if (collides == false && sprite->getEntity()->getVisibility()) {
                    sprite->getEntity()->setVisibility(false);
                    if (behaviour)
                        behaviour->onViewLeave();
                }
            });
        }

      private:
        static Rect<float> getRelativeBounds(CameraComponent *camera)
        {
            Vector2<float> position;

            if (PositionComponent *positionComponent = camera->getEntity()->getComponent<PositionComponent>()) {
                position.x = positionComponent->x;
                position.y = positionComponent->y;
            }
            return camera->viewport + position;
        }

        static Rect<float> getRelativeBounds(SpriteComponent *sprite)
        {
            Rect<float> bounds(0, 0, sprite->rect.width, sprite->rect.height);

            if (PositionComponent *positionComponent = sprite->getEntity()->getComponent<PositionComponent>()) {
                bounds.x = positionComponent->x;
                bounds.y = positionComponent->y;
            }
            return bounds;
        }
    };

}
