/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Game class
*/

#include "Game.hpp"

#include "SFML/Config.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "engine/core/AGame.hpp"
#include "utils/Singleton.hpp"
#include <thread>

namespace rtype::client {
    Game::Game()
        : lastUpdate_ { std::chrono::steady_clock::now() }
    { }

    void Game::resetClock()
    {
        this->lastUpdate_ = std::chrono::steady_clock::now();
    }

    long Game::getElapsedMillisecond() const
    {
        const auto &elapsed = std::chrono::steady_clock::now() - this->lastUpdate_;
        return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    }

    void Game::wait()
    {
        auto interval = std::chrono::milliseconds((long)(1000 / this->getFramerateLimit()));
        const auto &now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::milliseconds(this->getElapsedMillisecond());
        std::this_thread::sleep_until(now - elapsed + interval);
    }

    void Game::setWindowTitle(const std::string &title)
    {
        this->windowTitle_ = title;
    }

    void Game::setVideoMode(sf::VideoMode mode)
    {
        this->videoMode_ = mode;
    }

    void Game::setWindowStyle(sf::Uint32 style)
    {
        this->windowStyle_ = style;
    }

    sf::RenderWindow *Game::getWindow() const
    {
        return this->window_.get();
    }

    void Game::onInit()
    {
        this->window_ = std::make_unique<sf::RenderWindow>(
            this->videoMode_,
            this->windowTitle_,
            this->windowStyle_);
    }

    void Game::onBeforeUpdate()
    {
        this->window_->clear();
    }

    void Game::onAfterUpdate()
    {
        this->window_->display();
    }
}
