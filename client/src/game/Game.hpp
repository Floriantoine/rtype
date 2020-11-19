/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Game class
*/

#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "engine/core/AGame.hpp"
#include "utils/Singleton.hpp"

#include <string>
#include <unordered_map>

namespace rtype::client {

    class Game : public AGame, public Singleton<Game> {
      public:
        enum SceneFile {
            SCENE_MAIN_MENU,
            SCENE_LOBBY_MENU,
            SCENE_JOIN_MENU,
            SCENE_STAGE_1
        };

      private:
        std::chrono::steady_clock::time_point lastUpdate_;
        std::unique_ptr<sf::RenderWindow> window_;
        sf::VideoMode videoMode_ { 1920, 1080 };
        sf::Uint32 windowStyle_ { sf::Style::Default };
        std::string windowTitle_ { "Game" };
        const char *scenesDir_ { "./config_file/scene/" };
        static const std::unordered_map<SceneFile, const std::string> scenesNames_;
        std::unordered_map<SceneFile, std::shared_ptr<Scene>> scenesList_;

        void loadScene_(SceneFile, const std::string &);

      public:
        Game();
        ~Game() = default;

        void setScenesDir(const char *scenesDir);
        void resetClock() override;
        long getElapsedMillisecond() const override;
        void wait() override;
        void setWindowTitle(const std::string &title);
        void setVideoMode(sf::VideoMode mode);
        void setWindowStyle(sf::Uint32 style);
        sf::RenderWindow *getWindow() const;
        void onInit() override;
        void onBeforeUpdate() override;
        void onAfterUpdate() override;
    };
}
