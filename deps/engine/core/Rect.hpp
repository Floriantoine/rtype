/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Rectangle data class
*/

#pragma once

#include "./Vector2.hpp"

namespace rtype {

    /**
     * Rectangle class, holding the position and size of a rectangle
     * 
     * @tparam rectangle coordinates type
     */
    template <typename T = int>
    class Rect {
      public:
        T x { 0 };
        T y { 0 };
        T w { 0 };
        T h { 0 };

        /**
         * Construct a rectangle instance filled with zeros
         */
        Rect()
        { }
        /**
         * Construct a rectangle instance
         * 
         * @param x rectangle x coordinate
         * @param y rectangle y coordinate
         * @param w rectangle width
         * @param h rectangle height
         */
        Rect(T x, T y, T w, T h)
            : x { x }
            , y { y }
            , w { w }
            , h { h }
        { }

        /**
         * Checks if the rectangle intersects with another one
         * 
         * @param other other rectangle to check intersection with
         * 
         * @returns true if the two rectangles intersect, false otherwise
         */
        bool intersects(const Rect<T> &other) const
        {
            return this->x < other.x + other.w
                && this->x + this->w > other.x
                && this->y < other.y + other.h
                && this->y + this->h > other.y;
        }

        /**
         * Checks if the rectangle contains a point
         * 
         * @param x point x coordinate
         * @param y point y coordinate
         * 
         * @returns true if the rectangle contains the point, false otherwise
         */
        bool contains(T x, T y) const
        {
            return this->x < x
                && this->x + this->w > x
                && this->y < y
                && this->y + this->h > y;
        }

        /**
         * Checks if the rectangle contains a point
         * 
         * @param point point to check
         * 
         * @returns true if the rectangle contains the point, false otherwise
         */
        bool contains(const Vector2<T> &point) const
        {
            return this->contains(point.x, point.y);
        }

        Rect<T> operator+(const Vector2<T> &vec) const
        {
            return Rect(
                this->x + vec.x,
                this->y + vec.y,
                this->w,
                this->h);
        }
        Rect<T> &operator+=(const Vector2<T> &vec)
        {
            this->x += vec.x;
            this->y += vec.y;
            return *this;
        }

        Rect<T> operator-(const Vector2<T> &vec) const
        {
            return Rect(
                this->x - vec.x,
                this->y - vec.y,
                this->w,
                this->h);
        }
        Rect<T> &operator-=(const Vector2<T> &vec)
        {
            this->x -= vec.x;
            this->y -= vec.y;
            return *this;
        }
        
        bool operator==(const Rect<T> &other) const
        {
            return this->x == other.x
                && this->y == other.y
                && this->w == other.w
                && this->h == other.h;
        }
        bool operator!=(const Rect<T> &other) const
        {
            return !(this == other);
        }
    };

}