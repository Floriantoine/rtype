/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Player behaviour
*/

#pragma once

#include "../../../scene_loader/SceneLoader.hpp"
#include "../../core/ABehaviour.hpp"
#include "../../core/components/MissileComponent.hpp"
#include "../../core/components/PositionComponent.hpp"
#include "../../core/ecs/entity/Entity.hpp"
#include "../../core/components/SpriteComponent.hpp"

namespace rtype::server {

    class MoveHandler;

    class PlayerBehaviour : public ABehaviour {
        friend MoveHandler;

      private:
        PositionComponent *position_ = nullptr;
        MissileComponent *missile_ = nullptr;
        SpriteComponent *sprite_ = nullptr;

        bool isUpKeyPressed_ = false;
        bool isDownKeyPressed_ = false;
        bool isLeftKeyPressed_ = false;
        bool isRightKeyPressed_ = false;

        float move_ = 0.2;

        long keyElapsedTime_ = 0;
        long comeBackElapsedTime_ = 0;
        long shootElapsedTime_ = 0;

        int shootCooldown_ = 250;

        void init_()
        {
            if (this->position_ == nullptr) {
                this->position_ = this->getComponent<PositionComponent>();
            }
            if (this->missile_ == nullptr) {
                this->missile_ = this->getComponent<MissileComponent>();
            }
            if (this->sprite_ == nullptr) {
                this->sprite_ = this->getComponent<SpriteComponent>();
            }
        }

      public:
        void onUpdate(long elapsedTime) override
        {
            this->init_();
            if (this->isUpKeyPressed_) {
                this->position_->y -= this->move_ * elapsedTime;
                this->keyElapsedTime_ += elapsedTime;
            }
            if (this->isDownKeyPressed_) {
                this->position_->y += this->move_ * elapsedTime;
                this->keyElapsedTime_ -= elapsedTime;
            }
            if (this->isLeftKeyPressed_) {
                this->position_->x -= this->move_ * elapsedTime;
            }
            if (this->isRightKeyPressed_) {
                this->position_->x += this->move_ * elapsedTime;
            }
            this->shootElapsedTime_ += elapsedTime;
        }

        std::shared_ptr<Entity> shoot()
        {
            if (this->shootElapsedTime_ > shootCooldown_) {
                this->shootElapsedTime_ = 0;
                auto missile = JsonLoader::createEntity(*this->getEntity()->getEntityManager(), this->missile_->missileBody);
                auto missilePosition = missile->getComponent<PositionComponent>();

                missilePosition->x = this->position_->x + this->sprite_->rect.width;
                missilePosition->y = this->position_->y + this->sprite_->rect.height / 2;
                return missile;
            }
            return nullptr;
        }
    };
}
