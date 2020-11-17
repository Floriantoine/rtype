/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** 2-dimensional vector data class
*/

#pragma once

namespace rtype {

    template <typename T = int>
    class Vector2 {
      public:
        T x { 0 };
        T y { 0 };

        Vector2() = default;
        Vector2(T x, T y)
            : x { x }
            , y { y }
        { }
        Vector2(const Vector2<T> &other)
            : x { other.x }
            , y { other.y }
        { }
        ~Vector2() = default;

        Vector2<T> operator+(const Vector2<T> &other) const
        {
            return Vector2<T>(this->x + other.x, this->y + other.y);
        }
        Vector2<T> &operator+=(const Vector2<T> &other)
        {
            this->x += other.x;
            this->y += other.y;
            return *this;
        }

        Vector2<T> operator-(const Vector2<T> &other) const
        {
            return Vector2<T>(this->x - other.x, this->y - other.y);
        }
        Vector2<T> &operator-=(const Vector2<T> &other)
        {
            this->x -= other.x;
            this->y -= other.y;
            return *this;
        }

        Vector2<T> operator*(const Vector2<T> &other) const
        {
            return Vector2<T>(this->x * other.x, this->y * other.y);
        }
        Vector2<T> &operator*=(const Vector2<T> &other)
        {
            this->x *= other.x;
            this->y *= other.y;
            return *this;
        }

        Vector2<T> operator/(const Vector2<T> &other) const
        {
            return Vector2<T>(this->x / other.x, this->y / other.y);
        }
        Vector2<T> &operator/=(const Vector2<T> &other)
        {
            this->x /= other.x;
            this->y /= other.y;
            return *this;
        }

        bool operator==(const Vector2<T> &other) const
        {
            return this->x == other.x && this->y == other.y;
        }
        bool operator!=(const Vector2<T> &other) const
        {
            return !(this == other);
        }
    };

}