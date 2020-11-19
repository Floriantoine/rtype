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
#include "../components/PositionComponent.hpp"
#include "../components/CollideBoxComponent.hpp"
#include "../ecs/system/ASystem.hpp"
#include "../physics/CollisionChecker.hpp"
#include "../ABehaviourBase.hpp"
#include "../components/BehaviourComponent.hpp"

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
                Rect<float> bounds = this->getRelativeBounds(sprite);
                this->updateVisibility(sprite->getEntity(), bounds, cameraRect);
            });
            this->componentManager_->apply<CollideBoxComponent>([&](CollideBoxComponent *collideBox) {
                Rect<float> bounds = this->getRelativeBounds(collideBox);
                this->updateVisibility(collideBox->getEntity(), bounds, cameraRect);
            });
        }

      private:
        void updateVisibility(Entity *entity, const Rect<float> &objectBounds, const Rect<float> &cameraBounds)
        {
            BehaviourComponent *behaviourComponent = entity->getComponent<BehaviourComponent>();
            std::shared_ptr<ABehaviourBase> behaviour;
            if (behaviourComponent != nullptr)
                behaviour = behaviourComponent->getBehaviour<ABehaviourBase>();

            bool collides = CollisionChecker::collides<float>(cameraBounds, objectBounds);
            if (collides && entity->getVisibility() == false) {
                entity->setVisibility(true);
                if (behaviour)
                    behaviour->onViewEnter();
            } else if (collides == false && entity->getVisibility()) {
                entity->setVisibility(false);
                if (behaviour)
                    behaviour->onViewLeave();
            }
        }

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

        static Rect<float> getRelativeBounds(CollideBoxComponent *collideBox)
        {
            Rect<float> bounds(0, 0, collideBox->box.w, collideBox->box.h);

            if (PositionComponent *positionComponent = collideBox->getEntity()->getComponent<PositionComponent>()) {
                bounds.x = positionComponent->x;
                bounds.y = positionComponent->y;
            }
            return bounds;
        }
    };

}
