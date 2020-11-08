/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** ExclusiveLock
*/

#pragma once

#include "ILock.hpp"

#include <mutex>

namespace rtype {
    class ExclusiveLock : public ILock, private std::recursive_mutex {
      public:
        ExclusiveLock() = default;
        virtual ~ExclusiveLock() override = default;

        ExclusiveLock(const ExclusiveLock &other) = delete;
        ExclusiveLock &operator=(const ExclusiveLock &other) = delete;

        /**
        * @brief recursively lock the mutex
        */
        void lock() override
        {
            std::recursive_mutex::lock();
        }

        /**
        * @brief recursively try_lock the mutex
        */
        bool try_lock() override
        {
            return std::recursive_mutex::try_lock();
        }

        /**
        * @brief recursively unlock the mutex
        */
        void unlock() override
        {
            std::recursive_mutex::unlock();
        }

        /**
        * @brief returns a newly created std::unique_lock
        */
        std::unique_lock<ILock> unique_lock() override
        {
            return std::unique_lock<ILock>(*this);
        }
    };
}
