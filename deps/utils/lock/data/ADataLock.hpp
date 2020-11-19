/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** ADataLock
*/

#pragma once

#include "../ILock.hpp"

#include <condition_variable>
#include <functional>

namespace rtype {

    template <typename T>
    class ADataLock : public ILock {
      protected:
        T resource_;
        std::condition_variable_any condVar_;

      public:
        ADataLock(T &&data)
            : resource_ { std::move(data) }
        { } 

        ADataLock(ADataLock<T> &&other) noexcept
        {
            ADataLock::operator=(std::move(other));
        }

        ADataLock<T> &operator=(ADataLock<T> &&other) noexcept
        {
            this->resource_ = std::move(other.resource_);
            return (*this);
        }

        ADataLock() = default;
        virtual ~ADataLock() override = default;

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

        /**
         * @brief alias to member function `apply`
         **/
        void operator()(std::function<void(T &)> function)
        {
            this->apply(function);
        }

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
         * @brief locks the mutex before applaying `function` onto the stored variable
         **/
        void apply(std::function<void(T &)> function)
        {
            auto lock = this->unique_lock();

            function(this->resource_);
        }

        /**
         * @brief tries to lock the mutex before applaying `function` onto the stored variable
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
         * if the predicate is resolved, the mutex is locked
         * this call is unlocked by a call to notify_one or notify_all
         *
         * @param predicate
         * @return std::unique_lock<ADataLock<T>>
         **/
        std::unique_lock<ADataLock<T>> wait(std::function<bool(const T &)> predicate)
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
         * @return std::unique_lock<ADataLock<T>>
         **/
        std::unique_lock<ADataLock<T>> wait()
        {
            std::unique_lock<ADataLock<T>> unqLock(*this);

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