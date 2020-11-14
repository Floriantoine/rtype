/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Game class
*/

#pragma once

#include "./scene/SceneManager.hpp"

namespace rtype {

    class Game {
      private:
        SceneManager sceneManager_;
        bool isRunning { false };

      public:
        Game() = default;
        ~Game() = default;

        void run()
        {
            this->isRunning = true;
            while (this->isRunning) {
                // TODO: limit to 60hz
                this->sceneManager_.update();
            }
        }

        std::shared_ptr<Scene> createScene(std::size_t layer)
        {
            return this->sceneManager_.createScene(layer);
        }

        void destroyScene(std::shared_ptr<Scene> scene)
        {
            this->sceneManager_.destroyScene(scene);
        }

        std::shared_ptr<Scene> getScene(id_t sceneId)
        {
            return this->sceneManager_.getScene(sceneId);
        }
    };

}
