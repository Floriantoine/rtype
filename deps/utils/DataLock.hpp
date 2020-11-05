/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** DataLock
*/

#pragma once

#include "Exception.hpp"

#include <condition_variable>
#include <functional>
#include <mutex>

namespace RType {

    /**
     * @brief A child of std::recursive_mutex allowing you to store a variable directly associated to it's mutex
     *
     * @tparam T the type of variable to store
     */
    template <typename T>
    class DataLock : private std::recursive_mutex {
      private:
        T resource_;
        std::condition_variable_any condVar_;

      public:
        /**
         * @brief Construct a new DataLock object and stores a T variable
         *
         * @param data the variable to store
         **/
        DataLock(const T &data)
            : resource_ { std::move(data) }
        {
        }
        DataLock(DataLock<T> &&other)
        {
            *this = std::move(other);
        }
        DataLock<T> &operator=(DataLock<T> &&other)
        {
            this->resource_ = std::move(other.resource_);
            return (*this);
        }

        DataLock() = default;
        ~DataLock() = default;

        DataLock(DataLock<T> &other) = delete;
        DataLock<T> &operator=(const DataLock<T> &other) = delete;

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

        using std::recursive_mutex::unlock;

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
         * @brief Locks the mutex assossiated to the stored variable
         *
         * @return T &
         **/
        T &lock()
        {
            std::recursive_mutex::lock();
            return (this->resource_);
        }

        /**
         * @brief Tries to lock the mutex assossiated to the stored variable
         *
         * @return T * if it fails, a nullptr is returned
         **/
        T *try_lock()
        {
            if (!std::recursive_mutex::try_lock())
                return (nullptr);
            return (&this->resource_);
        }

        /**
         * @brief locks the mutex before applaying `function` onto the stored variable
         **/
        void apply(std::function<void(T &)> function)
        {
            auto lock = unique_lock();

            function(this->resource_);
        }

        /**
         * @brief tries to lock the mutex before applaying `function` onto the stored variable
         * if locking isn't successful, false is passed as second parameter to `function`, true otherwise
         **/
        void try_apply(std::function<void(T &, bool)> function)
        {
            function(this->resource_, std::recursive_mutex::try_lock());
            unlock();
        }

        /**
         * @brief returns a newly created unique_lock of the assossiated mutex
         **/
        std::unique_lock<DataLock> unique_lock()
        {
            return (std::unique_lock<DataLock>(*this));
        }

        /**
         * @brief waits for the stored variable to be modified
         * loops while `predicate` returns false
         * this call is unlocked by a call to notify_one or notify_all
         *
         * @param predicate
         * @return std::unique_lock<DataLock<T>>
         **/
        std::unique_lock<DataLock<T>> wait(std::function<bool(const T &)> predicate)
        {
            auto unqLock = unique_lock();

            this->condVar_.wait(unqLock, [&]() {
                return predicate(this->resource_);
            });
            return (unqLock);
        }

        /**
         * @brief waits for the stored variable to be modified
         * this call is unlocked by a call to notify_one or notify_all
         *
         * @return std::unique_lock<DataLock<T>>
         **/
        std::unique_lock<DataLock<T>> wait()
        {
            std::unique_lock<DataLock<T>> unqLock(*this);

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