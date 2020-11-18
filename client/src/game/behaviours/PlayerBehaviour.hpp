/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Player behaviour
*/

#pragma once

#include "engine/core/ABehaviour.hpp"
#include "engine/core/components/AnimationComponent.hpp"
#include "engine/core/components/PositionComponent.hpp"
#include "engine/core/components/SpriteComponent.hpp"
#include "engine/core/components/MissileComponent.hpp"

namespace rtype::client {

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

        int missileSpawnRate_ = 190;
        int animRate_ = 130;

        void init_();
        void onAnimation_(long elapsedTime);
        void onShoot_(long elapsedTime);

      public:
        void onUpdate(long elapsedTime) override;
        void onKeyPressed(const sf::Event &event) override;
        void onKeyReleased(const sf::Event &event) override;
        void onCollide(const CollisionData &collision) override;
    };

}
