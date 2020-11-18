/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Player behaviour
*/

#pragma once

#include "engine/core/ABehaviour.hpp"
#include "engine/core/components/AnimationComponent.hpp"
#include "engine/core/components/MissileComponent.hpp"
#include "engine/core/components/PositionComponent.hpp"
#include "engine/core/components/SpriteComponent.hpp"
#include "scene_loader/SceneLoader.hpp"

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

        void init_();

      public:
        void onUpdate(long elapsedTime) override;
        std::shared_ptr<Entity> shoot();
    };
}
