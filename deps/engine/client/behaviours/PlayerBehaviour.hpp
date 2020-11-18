/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Player behaviour
*/

#pragma once

#include "../../../scene_loader/SceneLoader.hpp"
#include "../../core/ABehaviour.hpp"
#include "../../core/components/AnimationComponent.hpp"
#include "../../core/components/PositionComponent.hpp"
#include "../../core/components/SpriteComponent.hpp"
#include "../../core/ecs/entity/Entity.hpp"
#include "../../core/components/MissileComponent.hpp"
#include "../CollideGroups.hpp"
#include "SFML/Window/Event.hpp"

namespace rtype {

    class PlayerBehaviour : public ABehaviour {
      private:
        PositionComponent *position_ = nullptr;
        AnimationComponent *animation_ = nullptr;
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

        int missileSpawnRate_ = 160;
        int animRate_ = 130;

        void init_()
        {
            if (this->position_ == nullptr) {
                this->position_ = this->getComponent<PositionComponent>();
            }
            if (this->animation_ == nullptr) {
                this->animation_ = this->getComponent<AnimationComponent>();
            }
            if (this->missile_ == nullptr) {
                this->missile_ = this->getComponent<MissileComponent>();
            }
            if (this->sprite_ == nullptr) {
                this->sprite_ = this->getComponent<SpriteComponent>();
            }
        }

        void onAnimation_(long elapsedTime)
        {
            int currentFrame = this->animation_->currentFrame;
            int totalFrame = this->animation_->totalFrame - 1;
            int middleFrame = totalFrame / 2;

            if (this->keyElapsedTime_) {
                int step = this->keyElapsedTime_ / this->animRate_;

                if (step) {
                    this->keyElapsedTime_ %= this->animRate_;
                    if (currentFrame + step > totalFrame) {
                        this->animation_->currentFrame = totalFrame;
                    } else if (currentFrame + step < 0) {
                        this->animation_->currentFrame = 0;
                    } else
                        this->animation_->currentFrame += step;
                }
            }
            if (this->keyElapsedTime_ && !this->isDownKeyPressed_ && !this->isUpKeyPressed_) {
                this->comeBackElapsedTime_ += elapsedTime;

                int step = this->comeBackElapsedTime_ / this->animRate_;

                if (step) {
                    this->comeBackElapsedTime_ %= this->animRate_;

                    if (currentFrame - step > middleFrame) {
                        this->animation_->currentFrame -= step;
                    } else if (currentFrame + step < middleFrame) {
                        this->animation_->currentFrame += step;
                    } else {
                        this->animation_->currentFrame = middleFrame;
                        this->keyElapsedTime_ = 0;
                    }
                }
            }
        }

        void onShoot_(long elapsedTime)
        {
            this->shootElapsedTime_ += elapsedTime;

            if (this->shootElapsedTime_ / this->missileSpawnRate_ > 0) {
                this->shootElapsedTime_ %= this->missileSpawnRate_;
                auto missile = JsonLoader::createEntity(*this->getEntity()->getEntityManager(), this->missile_->missileBody);
                auto missilePosition = missile->getComponent<PositionComponent>();

                missilePosition->x = this->position_->x + this->sprite_->rect.width;
                missilePosition->y = this->position_->y + this->sprite_->rect.height / 2;
            }
        }

      public:
        void onInit() override
        {
        }

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
            this->onAnimation_(elapsedTime);
            this->onShoot_(elapsedTime);
        }

        void onKeyPressed(const sf::Event &event) override
        {
            switch (event.key.code) {
                case sf::Keyboard::Key::Z:
                    this->isUpKeyPressed_ = true;
                    break;
                case sf::Keyboard::Key::Q:
                    this->isLeftKeyPressed_ = true;
                    break;
                case sf::Keyboard::Key::S:
                    this->isDownKeyPressed_ = true;
                    break;
                case sf::Keyboard::Key::D:
                    this->isRightKeyPressed_ = true;
                    break;
                default:
                    break;
            }
        }

        void onKeyReleased(const sf::Event &event) override
        {
            switch (event.key.code) {
                case sf::Keyboard::Key::Z:
                    this->isUpKeyPressed_ = false;
                    break;
                case sf::Keyboard::Key::Q:
                    this->isLeftKeyPressed_ = false;
                    break;
                case sf::Keyboard::Key::S:
                    this->isDownKeyPressed_ = false;
                    break;
                case sf::Keyboard::Key::D:
                    this->isRightKeyPressed_ = false;
                    break;
                default:
                    break;
            }
        }

        void onMouseButtonPressed(const sf::Event &event) override
        {
        }

        void onCollide(const CollisionData &collision) override
        {
            if (collision.other.collideGroup != COLLIDE_GROUP_PLAYERS) {
                this->takeDamage(this->getHealth());
            }
        }
    };

}
