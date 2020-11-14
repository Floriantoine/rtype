/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** ExclusiveDataLock
*/

#pragma once

#include "../ExclusiveLock.hpp"
#include "ADataLock.hpp"

#include <condition_variable>
#include <functional>
#include <mutex>

namespace rtype {

    template <typename T>
    class ExclusiveDataLock : public ADataLock<T>, public ExclusiveLock {
      public:
        ExclusiveDataLock(T &&data)
            : ADataLock<T>(std::move(data))
        { }

        ExclusiveDataLock<T> &operator=(const ExclusiveDataLock<T> &other) = delete;
        ExclusiveDataLock(const ExclusiveDataLock<T> &other) = delete;

        ExclusiveDataLock() = default;
        virtual ~ExclusiveDataLock() override = default;

        /**
        * @brief calls ExclusiveLock::lock
        */
        void lock() override
        {
            ExclusiveLock::lock();
        }

        /**
        * @brief calls ExclusiveLock::try_lock
        */
        bool try_lock() override
        {
            return ExclusiveLock::try_lock();
        }

        /**
        * @brief calls ExclusiveLock::unlock
        */
        void unlock() override
        {
            ExclusiveLock::unlock();
        }

        /**
        * @brief calls ExclusiveLock::unique_lock
        */
        std::unique_lock<ILock> unique_lock() override
        {
            return ExclusiveLock::unique_lock();
        }

        /**
         * @brief waits for a notification before checking the predicate
         * if the predicate is resolved, the mutex is locked
         * this call is unlocked by a call to notify_one or notify_all
         *
         * @param predicate
         * @return std::unique_lock<ILock>
         **/
        std::unique_lock<ILock> wait(std::function<bool(const T &)> predicate)
        {
            auto unqLock = this->unique_lock();

            this->condVar_.wait(unqLock, [&]() {
                return predicate(this->resource_);
            });
            return (unqLock);
        }

        /**
         * @brief waits for a notification before locking the mutex
         *
         * @return std::unique_lock<ILock>
         **/
        std::unique_lock<ILock> wait()
        {
            std::unique_lock<ILock> unqLock(*this);

            this->condVar_.wait(unqLock);
            return (unqLock);
        }

        /**
         * @brief notifies one waiting thread to unlock their call to `wait`
         **/
        void notify_one()
        {
            this->condVar_.notify_one();
        }

        /**
         * @brief notifies all waiting threads to unlock their call to `wait`
         **/
        void notify_all()
        {
            this->condVar_.notify_all();
        }
    };
}