/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Game class
*/

#pragma once

#include "../core/AGame.hpp"

#include <chrono>
#include <iostream>
#include <thread>

namespace rtype {
    namespace client {

        class Game : public AGame {
          private:
            std::chrono::steady_clock::time_point lastUpdate_;

          public:
            Game()
                : lastUpdate_ { std::chrono::steady_clock::now() }
            { }
            ~Game() = default;

            long getElapsedMillisecond() const override
            {
                auto elapsed = std::chrono::steady_clock::now() - this->lastUpdate_;
                return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
            }

            void tick() override
            {
                auto expectedInterval = std::chrono::milliseconds((long)(1000 / this->getFramerateLimit()));
                auto elapsedTime = std::chrono::milliseconds(this->getElapsedMillisecond());
                auto maxInterval = expectedInterval > elapsedTime
                    ? expectedInterval
                    : elapsedTime;
                auto now = std::chrono::steady_clock::now();
                auto nextTickTime = now - elapsedTime + maxInterval * 2;

                this->lastUpdate_ = nextTickTime - expectedInterval;
                std::this_thread::sleep_until(nextTickTime);
            }
        };

    }
}
