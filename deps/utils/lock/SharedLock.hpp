/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** SharedLock
*/

#pragma once

#include "ILock.hpp"
#include "boost/thread/condition_variable.hpp"
#include "boost/thread/lock_types.hpp"
#include "boost/thread/shared_mutex.hpp"

namespace rtype {
    class SharedLock : public ILock, private boost::upgrade_mutex {
      protected:
        unsigned pendingExclusiveLock_ { 0 };
        boost::condition_variable_any rwCondVar_;

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
            boost::upgrade_mutex::lock();
            --this->pendingExclusiveLock_;
        }

        /**
        * @brief lock the mutex without exclusivity
        */
        void lock_shared()
        {
            boost::shared_lock<boost::upgrade_mutex> lock(*this);

            this->rwCondVar_.wait(lock, [this] {
                return this->pendingExclusiveLock_ == 0;
            });
            lock.release();
        }

        /**
        * @brief try_lock the mutex with exclusivity
        */
        bool try_lock() override
        {
            return boost::upgrade_mutex::try_lock();
        }

        /**
        * @brief try_lock the mutex without exclusivity
        */
        using boost::upgrade_mutex::try_lock_shared;

        /**
        * @brief unlock the exclusivity locked mutex
        */
        void unlock() override
        {
            boost::upgrade_mutex::unlock();
            this->rwCondVar_.notify_all();
        }

        /**
        * @brief try_lock the shared_locked mutex
        */
        using boost::upgrade_mutex::unlock_shared;

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
        boost::shared_lock<SharedLock> shared_lock()
        {
            return boost::shared_lock<SharedLock>(*this);
        }

        /**
        * @brief returns a newly created shared_lock
        */
        boost::upgrade_lock<SharedLock> upgrade_lock()
        {
            return boost::upgrade_lock<SharedLock>(*this);
        }

        using boost::upgrade_mutex::lock_upgrade;
        using boost::upgrade_mutex::try_lock_upgrade;
        using boost::upgrade_mutex::unlock_upgrade;
    };
}
