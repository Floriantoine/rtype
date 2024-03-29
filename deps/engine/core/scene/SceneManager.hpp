/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** SceneManager
*/

#pragma once

#include "Scene.hpp"

#include <algorithm>
#include <map>
#include <memory>
#include <vector>

namespace rtype {
    class SceneManager {
      private:
        std::multimap<std::size_t, std::shared_ptr<Scene>> orderedScenes_;

      public:
        SceneManager() = default;
        ~SceneManager() = default;

        // Create a scene from a file
        std::shared_ptr<Scene> createScene(std::size_t layer)
        {
            std::shared_ptr<Scene> new_scene = std::make_shared<Scene>();

            this->orderedScenes_.emplace(std::make_pair(layer, new_scene));
            return new_scene;
        }

        void destroyScene(std::shared_ptr<Scene> scene)
        {
            id_t sceneId = scene->getId();
            auto it = this->orderedScenes_.cbegin();
            auto end = this->orderedScenes_.cend();

            for (; it != end; ++it) {
                if (it->second->getId() == sceneId) {
                    this->orderedScenes_.erase(it);
                    break;
                }
            }
        }

        std::shared_ptr<Scene> getScene(id_t sceneId)
        {
            for (const auto &it : this->orderedScenes_) {
                if (it.second->getId() == sceneId) {
                    return it.second;
                }
            }
            return nullptr;
        }

        void update(long elapsedTime)
        {
            for (auto &scene : this->orderedScenes_) {
                scene.second->update(elapsedTime);
            }
        }

        void update(ASystem::system_group_e group, long elapsedTime)
        {
            for (auto &scene : this->orderedScenes_) {
                scene.second->update(group, elapsedTime);
            }
        }

        /**
         * Set a scene state to paused
         * 
         * @param sceneId scene id
         */
        void pauseScene(id_t sceneId)
        {
            this->getScene(sceneId)->setState(Scene::State::STATE_PAUSED);
        }

        /**
         * Set a scene state to inactive
         * 
         * @param sceneId scene id
         */
        void disableScene(id_t sceneId)
        {
            this->getScene(sceneId)->setState(Scene::State::STATE_INACTIVE);
        }

        /**
         * Switch to a given scene, disabling others
         * 
         * @param sceneId scene id
         */
        void goToScene(id_t sceneId)
        {
            bool found = false;
            for (const auto &it: this->orderedScenes_) {
                if (it.second->getId() == sceneId) {
                    found = true;
                    it.second->setState(Scene::State::STATE_RUNNING);
                } else {
                    it.second->setState(Scene::State::STATE_INACTIVE);
                }
            }
            if (!found) {
                throw std::runtime_error("Specified scene id doesn't exist");
            }
        }
    };
}
