/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Game class
*/

#pragma once

#include "../core/AGame.hpp"
#include "../utils/Singleton.hpp"
#include "SFML/Window.hpp"

#include <chrono>
#include <iostream>
#include <thread>

namespace rtype {
    namespace client {

        class Game : public AGame, public Singleton<Game> {
          private:
            std::chrono::steady_clock::time_point lastUpdate_;
            std::unique_ptr<sf::Window> window_;
            sf::VideoMode videoMode_ { 1920, 1080 };
            sf::Uint32 windowStyle_ { sf::Style::Default };
            std::string windowTitle_ { "Game" };

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

            void setWindowTitle(const std::string &title)
            {
                this->windowTitle_ = title;
            }

            void setVideoMode(sf::VideoMode mode)
            {
                this->videoMode_ = mode;
            }

            void setWindowStyle(sf::Uint32 style)
            {
                this->windowStyle_ = style;
            }

            sf::Window *getWindow() const
            {
                return this->window_.get();
            }

            void onInit() override
            {
                this->window_ = std::make_unique<sf::Window>(
                    this->videoMode_,
                    this->windowTitle_,
                    this->windowStyle_);
            }

            void onTick() override
            {
                this->window_->display();
            }
        };

    }
}
