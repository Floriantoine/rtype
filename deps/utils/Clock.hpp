/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Clock
*/

#pragma once

#include <chrono>
#include <string>

namespace rtype {
    class Clock {
      public:
        typedef std::chrono::steady_clock::time_point time_point_t;
        typedef long millisec_t;

      private:
        time_point_t start_;

      public:
        Clock()
            : start_ { this->Now() }
        {
        }
        Clock(const Clock &other)
            : start_ { other.start_ }
        {
        }
        ~Clock() = default;

        /**
         * @brief Reset the internal time reference
         **/
        void reset()
        {
            this->start_ = this->Now();
        }

        /**
         * @brief Get the elapsed time in milliseconds between the current time and the internal reference
         *
         * @return millisec_t (a.k.a. long int)
         **/
        millisec_t getElapsedMillisecond() const
        {
            const auto &end = this->Now();
            return (std::chrono::duration_cast<std::chrono::milliseconds>(end - this->start_).count());
        }

        time_point_t getStartPoint() const
        {
            return this->start_;
        }

        static time_point_t Now() noexcept
        {
            return std::chrono::steady_clock::now();
        }

        static std::string GetCurrentTime() noexcept
        {
            auto timePoint = std::chrono::system_clock::now();
            std::time_t time = std::chrono::system_clock::to_time_t(timePoint);
            std::string humanTime = std::ctime(&time);

            humanTime = humanTime.substr(0, humanTime.size() - 1);
            return (humanTime);
        }
    };
}