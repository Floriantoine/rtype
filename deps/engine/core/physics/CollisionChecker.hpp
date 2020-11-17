/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Collision checker util class
*/

#pragma once

#include "../components/CollideBoxComponent.hpp"
#include "./CollisionData.hpp"
#include "../Vector2.hpp"
#include "../Rect.hpp"

namespace rtype {

    /**
     * Abstraction class providing methods for checking collisions between different types
     */
    class CollisionChecker
    {
      public:
        /**
         * Check collision between two rectangles
         * 
         * @tparam coordinates type
         * 
         * @param rect first rectangle
         * @param other second rectangle
         * 
         * @returns true if the two rectangles intersect, false otherwise
         */
        template<typename T = int>
        static bool collides(const Rect<T> &rect, const Rect<T> &other)
        {
            return rect.intersects(other);
        }

        /**
         * Check collision between a rectangle and a point
         * 
         * @tparam coordinates type
         * 
         * @param rect rectangle to check
         * @param point point to check
         * 
         * @returns true if the rectangle collides with the point, false otherwise
         */
        template<typename T = int>
        static bool collides(const Rect<T> &rect, const Vector2<T> &point)
        {
            return rect.contains(rect, point);
        }

        /**
         * Check collision between a rectangle and a point
         * 
         * @tparam coordinates type
         * 
         * @param rect rectangle to check
         * @param x point x coordinate
         * @param y point y coordinate
         * 
         * @returns true if the rectangle collides with the point, false otherwise
         */
        template<typename T = int>
        static bool collides(const Rect<T> &rect, T x, T y)
        {
            return rect.contains(rect, x, y);
        }
    };

}