/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Collision data structure
*/

#pragma once

#include "../Rect.hpp"
#include "../ecs/entity/Entity.hpp"

namespace rtype {

    /**
     * Data concerning an entity implied in a collision
     */
    class ColliderData {
      public:
        Entity *entity;
        int collideGroup;
        const Rect<float> relativeCollideBox;

        ColliderData(Entity *entity, int collideGroup, const Rect<float> &&relativeCollideBox)
            : entity ( entity )
            , collideGroup ( collideGroup )
            , relativeCollideBox ( std::move(relativeCollideBox) )
        {}
        ~ColliderData() = default;
    };

    /**
     * Data concerning a collision with an entity
     */
    class CollisionData {
      public:
        const ColliderData &self;
        const ColliderData &other;

        CollisionData(const ColliderData &self, const ColliderData &other)
            : self { self }
            , other { other }
        { }
        ~CollisionData() = default;
    };

}