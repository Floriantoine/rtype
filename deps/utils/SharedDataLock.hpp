/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** SharedDataLock
*/

#pragma once

#include <condition_variable>
#include <functional>
#include <mutex>
#include <shared_mutex>

namespace rtype {

    /**
     * @brief A child of std::shared_mutex allowing you to store a variable directly associated to it's mutex
     *
     * @tparam T the type of variable to store
     */
    template <typename T>
    class SharedDataLock : private std::shared_mutex {
      private:
        T resource_;
        unsigned pendingExclusiveLock_ { 0 };
        std::condition_variable_any rwCondVar_;
        std::condition_variable_any condVar_;

      public:
        /**
         * @brief Construct a new SharedDataLock object and stores a T variable
         *
         * @param data the variable to store
         **/
        SharedDataLock(T &&data)
            : resource_ { std::move(data) }
        {
        }
        SharedDataLock(SharedDataLock<T> &&other)
        {
            *this = std::move(other);
        }
        SharedDataLock<T> &operator=(SharedDataLock<T> &&other)
        {
            this->resource_ = std::move(other.resource_);
            return (*this);
        }

        SharedDataLock() = default;
        ~SharedDataLock() = default;

        SharedDataLock(const T &data) = delete;
        SharedDataLock(const SharedDataLock<T> &other) = delete;
        SharedDataLock<T> &operator=(const SharedDataLock<T> &other) = delete;

        /**
         * @brief access the object stored
         *
         * @return T *
         **/
        T *operator->()
        {
            return (&this->resource_);
        }

        /**
         * @brief access the object stored as a const
         *
         * @return T *
         **/
        const T *operator->() const
        {
            return (&this->resource_);
        }

        /**
         * @brief access the object stored
         *
         * @return T *
         **/
        T &operator*()
        {
            return (this->resource_);
        }

        /**
         * @brief access the object stored as a const
         *
         * @return T *
         **/
        const T &operator*() const
        {
            return (this->resource_);
        }

        using std::shared_mutex::try_lock;
        using std::shared_mutex::try_lock_shared;
        using std::shared_mutex::unlock_shared;

        /**
         * @brief returns a read-only reference to the stored variable
         *
         * @return const T &
         **/
        const T &read() const
        {
            return (this->resource_);
        }

        /**
        * @brief blocking call to lock (exclusively) the shared_mutex
        */
        void lock()
        {
            ++this->pendingExclusiveLock_;
            std::shared_mutex::lock();
            --this->pendingExclusiveLock_;
        }

        /**
        * @brief blocking call to lock_shared the shared_mutex
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
        * @brief unlocks the exclusively locked shared_mutex
        */
        void unlock()
        {
            std::shared_mutex::unlock();
            this->rwCondVar_.notify_all();
        }

        /**
         * @brief exclusively locks the mutex before applaying `function` onto the stored variable
         **/
        void apply(std::function<void(T &)> function)
        {
            this->lock();
            function(this->resource_);
            this->unlock();
        }

        /**
         * @brief tries to exclusively lock the mutex before applaying `function` onto the stored variable
         * if locking isn't successful, false is passed as second parameter to `function`, true otherwise
         **/
        void try_apply(std::function<void(T &, bool)> function)
        {
            bool locked = this->try_lock();

            function(this->resource_, locked);
            if (locked) {
                this->unlock();
            }
        }

        /**
         * @brief waits for a notification before checking the predicate
         * if the predicate is resolved, the mutex is exclusively locked
         * this call is unblocked by a call to notify_one or notify_all
         *
         * @param predicate
         **/
        std::unique_lock<SharedDataLock<T>> wait(std::function<bool(const T &)> predicate)
        {
            std::unique_lock<SharedDataLock<T>> lock(*this);

            this->condVar_.wait(lock, [&]() {
                return predicate(this->resource_);
            });
            return lock;
        }

        /**
         * @brief waits for a notification before exclusively locking the mutex
         **/
        std::unique_lock<SharedDataLock<T>> wait()
        {
            std::unique_lock<SharedDataLock<T>> lock(*this);

            this->condVar_.wait(lock);
            return lock;
        }

        /**
         * @brief waits for a notification before checking the predicate
         * if the predicate is resolved, the mutex is shared locked
         * this call is unblocked by a call to notify_one or notify_all
         *
         * @param predicate
         **/
        std::shared_lock<SharedDataLock<T>> wait_shared(std::function<bool(const T &)> predicate)
        {
            std::shared_lock<SharedDataLock<T>> lock(*this);

            this->condVar_.wait(lock, [&]() {
                return predicate(this->resource_);
            });
            return lock;
        }

        /**
         * @brief waits for a notification before share-locking the mutex
         *
         * @return std::unique_lock<SharedDataLock<T>>
         **/
        std::shared_lock<SharedDataLock<T>> wait_shared()
        {
            std::shared_lock<SharedDataLock<T>> lock(*this);

            this->condVar_.wait(lock);
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