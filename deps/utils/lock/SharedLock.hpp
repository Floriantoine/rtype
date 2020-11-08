/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** SharedLock
*/

#pragma once

#include "ILock.hpp"

#include <shared_mutex>

namespace rtype {
    class SharedLock : public ILock, private std::shared_mutex {
      protected:
        unsigned pendingExclusiveLock_ { 0 };
        std::condition_variable_any rwCondVar_;

      public:
        SharedLock() = default;
        virtual ~SharedLock() override = default;

        SharedLock(const SharedLock &other) = delete;
        SharedLock &operator=(const SharedLock &other) = delete;

        /**
        * @brief lock the mutex with exclusivity
        */
        void lock() override
        {
            ++this->pendingExclusiveLock_;
            std::shared_mutex::lock();
            --this->pendingExclusiveLock_;
        }

        /**
        * @brief lock the mutex without exclusivity
        */
        void lock_shared()
        {
            std::shared_lock<std::shared_mutex> lock(*this);

            this->rwCondVar_.wait(lock, [this] {
                return this->pendingExclusiveLock_ == 0;
            });
            std::shared_mutex::lock_shared();
        }

        /**
        * @brief try_lock the mutex with exclusivity
        */
        bool try_lock() override
        {
            return std::shared_mutex::try_lock();
        }

        /**
        * @brief try_lock the mutex without exclusivity
        */
        using std::shared_mutex::try_lock_shared;

        /**
        * @brief unlock the exclusivity locked mutex
        */
        void unlock() override
        {
            std::shared_mutex::unlock();
            this->rwCondVar_.notify_all();
        }

        /**
        * @brief try_lock the shared_locked mutex
        */
        using std::shared_mutex::unlock_shared;

        /**
        * @brief returns a newly created unique_lock
        */
        std::unique_lock<ILock> unique_lock() override
        {
            return std::unique_lock<ILock>(*this);
        }

        /**
        * @brief returns a newly created shared_lock
        */
        std::shared_lock<SharedLock> shared_lock()
        {
            return std::shared_lock<SharedLock>(*this);
        }
    };
}
