/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Clock
*/

#pragma once

#include <chrono>
#include <string>

namespace Utils {

    class Clock {

    private:
        std::chrono::_V2::steady_clock::time_point start_;

    public:
        Clock() : start_ { std::chrono::steady_clock::now() }
        {
        }
        Clock(const Clock &other) : start_ { other.start_ }
        {
        }
        ~Clock() = default;

        typedef long millisec_t;

        /**
         * @brief Reset the internal time reference
         **/
        void reset()
        {
            this->start_ = std::chrono::steady_clock::now();
        }

        /**
         * @brief Get the elapsed time in milliseconds between the current time and the internal reference
         *
         * @return millisec_t (a.k.a. long int)
         **/
        millisec_t getElapsedMillisecond() const
        {
            const auto &end = std::chrono::steady_clock::now();
            return (std::chrono::duration_cast<std::chrono::milliseconds>(end - this->start_).count());
        }

        static std::string getCurrentTime() noexcept
        {
            auto timePoint = std::chrono::system_clock::now();
            std::time_t time = std::chrono::system_clock::to_time_t(timePoint);
            std::string humanTime = std::ctime(&time);

            humanTime = humanTime.substr(0, humanTime.size() - 1);
            return (humanTime);
        }
    };
}