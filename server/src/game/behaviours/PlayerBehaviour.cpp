/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Player behaviour
*/

#include "./PlayerBehaviour.hpp"

#include "engine/core/ecs/entity/Entity.hpp"
#include "game/CollideGroups.hpp"

namespace rtype::server {
    void PlayerBehaviour::init_()
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

    void PlayerBehaviour::onUpdate(long elapsedTime)
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
        this->sendPosition(this->position_);
    }

    std::shared_ptr<Entity> PlayerBehaviour::shoot()
    {
        if (this->shootElapsedTime_ > shootCooldown_) {
            this->shootElapsedTime_ = 0;
            auto missile = JsonLoader::createEntity(*this->getEntity()->getEntityManager(), this->missile_->missileBody);
            auto missilePosition = missile->getComponent<PositionComponent>();

            missilePosition->x = this->position_->x + this->sprite_->rect.width;
            missilePosition->y = this->position_->y + this->sprite_->rect.height / 2.0;
            return missile;
        }
        return nullptr;
    }
}
