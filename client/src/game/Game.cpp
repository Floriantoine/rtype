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

    const std::unordered_map<Game::SceneFile, const std::string> Game::scenesNames_ = {
        { Game::SceneFile::SCENE_MAIN_MENU, "menu.json" },
        { Game::SceneFile::SCENE_LOBBY_MENU, "lobby.json" },
        { Game::SceneFile::SCENE_JOIN_MENU, "join.json" },
        { Game::SceneFile::SCENE_STAGE_1, "stage1.json" }
    };

    void Game::setScenesDir(const char *scenesDir)
    {
        this->scenesDir_ = scenesDir;
    }

    void Game::loadScene_(Game::SceneFile scene_id, const std::string &filename)
    {
        auto scene = JsonLoader::createScene(*this, this->scenesDir_ + filename);

        scene->createSystem<BehaviourSystem>();
        scene->createSystem<CameraSystem>();
        scene->createSystem<CollisionSystem>();
        scene->createSystem<HealthSystem>();
        scene->createSystem<AnimationSystem>();
        scene->createSystem<EventSystem>();
        scene->createSystem<SpriteSystem>();
        scene->createSystem<TextSystem>();
        scene->createSystem<InputSystem>();
        scene->createSystem<BackgroundSystem>();
        this->scenesList_[scene_id] = scene;
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
        for (const auto &it: this->scenesNames_) {
            this->loadScene_(it.first, it.second);
        }
        this->goToScene(this->scenesList_[SCENE_MAIN_MENU]->getId());
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
