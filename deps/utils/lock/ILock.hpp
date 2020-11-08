/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** ILock
*/

#pragma once

#include <mutex>

namespace rtype {
    class ILock {
      public:
        ILock(ILock &&other) = default;
        ILock &operator=(ILock &&other) = default;
        ILock() = default;
        virtual ~ILock() = default;

        ILock(const ILock &other) = delete;
        ILock &operator=(const ILock &other) = delete;

        virtual void lock() = 0;
        virtual bool try_lock() = 0;
        virtual void unlock() = 0;
        virtual std::unique_lock<ILock> unique_lock() = 0;
    };
}
