#pragma once

#include <iostream>
#include <shared_mutex>
#include <condition_variable>

namespace Utils {

class rw_lock
{
    private:
        int awaitingWrite_ { 0 };
        std::shared_timed_mutex mutex_;
        std::condition_variable_any cv_;

    public:
        rw_lock() = default;
        rw_lock(const rw_lock &) = delete;
        rw_lock(rw_lock &&) = delete;
        ~rw_lock() = default;

        rw_lock &operator=(const rw_lock &) = delete;

        void lock_read()
        {
            std::shared_lock<std::shared_timed_mutex> lock(this->mutex_);
            this->cv_.wait(lock, [this]{
                return this->awaitingWrite_ == false;
            });
            this->mutex_.lock_shared();
        }

        void unlock_read()
        {
            this->mutex_.unlock_shared();
        }

        void lock_write()
        {
            ++this->awaitingWrite_;
            this->mutex_.lock();
            --this->awaitingWrite_;
        }

        void unlock_write()
        {
            this->mutex_.unlock();
            this->cv_.notify_all();
        }
};

}
