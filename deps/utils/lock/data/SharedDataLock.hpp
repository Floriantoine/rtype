/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** SharedDataLock
*/

#pragma once

#include "ADataLock.hpp"
#include "../SharedLock.hpp"

#include <condition_variable>
#include <functional>
#include <shared_mutex>

namespace rtype {

    template <typename T>
    class SharedDataLock : public ADataLock<T>, public SharedLock {
      public:
        SharedDataLock(T &&data)
            : ADataLock<T>(std::move(data))
        { }

        SharedDataLock<T> &operator=(const SharedDataLock<T> &other) = delete;
        SharedDataLock(const SharedDataLock<T> &other) = delete;

        SharedDataLock() = default;
        virtual ~SharedDataLock() override = default;

        /**
        * @brief calls SharedLock::lock
        */
        void lock() override
        {
            SharedLock::lock();
        }

        /**
        * @brief calls SharedLock::try_lock
        */
        bool try_lock() override
        {
            return SharedLock::try_lock();
        }

        /**
        * @brief calls SharedLock::unlock
        */
        void unlock() override
        {
            SharedLock::unlock();
        }

        /**
        * @brief calls SharedLock::unique_lock
        */
        std::unique_lock<ILock> unique_lock() override
        {
            return SharedLock::unique_lock();
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
            auto unqLock = this->unique_lock();

            this->condVar_.wait(unqLock);
            return (unqLock);
        }

        /**
         * @brief waits for a notification before checking the predicate
         * if the predicate is resolved, the mutex is shared locked
         * this call is unblocked by a call to notify_one or notify_all
         *
         * @param predicate
         **/
        std::shared_lock<ILock> wait_shared(std::function<bool(const T &)> predicate)
        {
            auto sharedLock = this->shared_lock();

            this->condVar_.wait(sharedLock, [&]() {
                return predicate(this->resource_);
            });
            return lock;
        }

        /**
         * @brief waits for a notification before share-locking the mutex
         *
         * @return std::unique_lock<ILock>
         **/
        std::shared_lock<ILock> wait_shared()
        {
            auto sharedLock = this->shared_lock();

            this->condVar_.wait(sharedLock);
            return lock;
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