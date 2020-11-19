/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Game class
*/

#include "Game.hpp"
#include "scene_loader/SceneLoader.hpp"

#include "engine/core/systems/BehaviourSystem.hpp"
#include "engine/core/systems/CameraSystem.hpp"
#include "engine/core/systems/CollisionSystem.hpp"
#include "engine/core/systems/HealthSystem.hpp"

#include "game/systems/AnimationSystem.hpp"
#include "game/systems/EventSystem.hpp"
#include "game/systems/SpriteSystem.hpp"
#include "game/systems/TextSystem.hpp"
#include "game/systems/InputSystem.hpp"
#include "game/systems/BackgroundSystem.hpp"

#include "SFML/Config.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "engine/core/AGame.hpp"
#include "utils/Singleton.hpp"
#include <thread>

namespace rtype::client {

    void Game::setScenesDir(const char *scenesDir)
    {
        this->scenesDir_ = scenesDir;
    }

    bool Game::loadScene_(const std::string &filename)
    {
        try {
            auto scene = JsonLoader::createScene(*this, this->scenesDir_ + filename);

            scene->createSystem<BehaviourSystem>();
            scene->createSystem<CameraSystem>();
            scene->createSystem<CollisionSystem>();
            scene->createSystem<HealthSystem>();
            scene->createSystem<AnimationSystem>();
            scene->createSystem<EventSystem>();
            scene->createSystem<TextSystem>();
            scene->createSystem<InputSystem>();
            scene->createSystem<SpriteSystem>();
            scene->createSystem<BackgroundSystem>();
            this->scenesList_[filename] = scene;
            return true;
        } catch (const Exception &e) {
            std::cerr << "error: " << e.what() << std::endl;
            return false;
        }
    }

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
        this->goToScene("menu.json");
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

    void Game::goToScene(const std::string &sceneName)
    {
        for (const auto &it: this->scenesList_) {
            if (it.first == sceneName) {
                AGame::goToScene(it.second->getId());
                return;
            }
        }
        if (this->loadScene_(sceneName) == true) {
            this->goToScene(sceneName);
        } else {
            std::cerr << "warn: scene name '" + sceneName + "' is not registered. Ignoring." << std::endl;
        }
    }

}
