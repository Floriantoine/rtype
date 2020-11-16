/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Player behaviour
*/

#pragma once

#include "../../core/components/AnimationComponent.hpp"
#include "../../core/components/PositionComponent.hpp"
#include "../../core/ecs/entity/Entity.hpp"
#include "../../core/ABehaviour.hpp"
#include "SFML/Window/Event.hpp"

#include <iostream>

namespace rtype {

    class PlayerBehaviour : public ABehaviour {
      private:
        PositionComponent *position_ = nullptr;
        AnimationComponent *animation_ = nullptr;

        bool isUpKeyPressed_ = false;
        bool isDownKeyPressed_ = false;
        bool isLeftKeyPressed_ = false;
        bool isRightKeyPressed_ = false;

        float move_ = 0.2;

        long UpElapsedTime_ = 0;
        long DownElapsedTime_ = 0;
        long GetMiddleElapsedTime_ = 0;

        int animRate_ = 30;

        void onAnimation_()
        {
            if (this->animation_ == nullptr) {
                this->animation_ = this->getComponent<AnimationComponent>();
            }

            if (this->UpElapsedTime_ && this->isUpKeyPressed_) {
                if (this->animation_->currentFrame + 1 < this->animation_->totalFrame) {
                    int diff = this->animation_->totalFrame - this->animation_->currentFrame + 1;
                    int step = this->UpElapsedTime_ / this->animRate_;

                    if (step > diff)
                        step = diff;
                    this->animation_->currentFrame += step;
                }
            }
            if (this->DownElapsedTime_ && this->isDownKeyPressed_) {
                if (this->animation_->currentFrame != 0) {
                    int diff = this->animation_->currentFrame;
                    int step = this->DownElapsedTime_ / this->animRate_;

                    if (step > diff)
                        step = diff;
                    this->animation_->currentFrame -= step;
                }
            }
        }

      public:
        void onInit() override
        {
        }

        void onUpdate(long elapsedTime) override
        {
            if (this->position_ == nullptr) {
                this->position_ = this->getComponent<PositionComponent>();
            }
            if (this->isUpKeyPressed_) {
                this->position_->y -= this->move_ * elapsedTime;
                this->UpElapsedTime_ += elapsedTime;
            } else {
                this->UpElapsedTime_ = 0;
            }

            if (this->isDownKeyPressed_) {
                this->position_->y += this->move_ * elapsedTime;
                this->DownElapsedTime_ += elapsedTime;
            } else {
                this->DownElapsedTime_ = 0;
            }
            if (this->isLeftKeyPressed_) {
                this->position_->x -= this->move_ * elapsedTime;
            }
            if (this->isRightKeyPressed_) {
                this->position_->x += this->move_ * elapsedTime;
            }
            this->onAnimation_();
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
            std::cout << "clicked (" << event.mouseButton.x << ":" << event.mouseButton.y << ")" << std::endl;
        }

        void onCollide() override
        {
        }
    };

}
