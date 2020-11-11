#pragma once

#include <memory>
#include <vector>
#include <algorithm>
#include <map>
#include "Scene.hpp"

class SceneManager
{
private:
    std::multimap<std::size_t, std::shared_ptr<Scene>> orderedScenes_;

public:
    SceneManager() = default;
    ~SceneManager() = default;

    // Create a scene from a file
    std::shared_ptr<Scene> createScene(std::unique_ptr<Scene> &scene, std::size_t layer)
    {
        std::shared_ptr<Scene> new_scene = std::make_shared<Scene>(scene.release());

        this->orderedScenes_.emplace(std::make_pair(layer, new_scene));
        return new_scene;
    }

    void destroyScene(std::shared_ptr<Scene> scene)
    {
        id_t sceneId = scene->getId();

        this->orderedScenes_.erase(std::remove_if(
            this->orderedScenes_.begin(),
            this->orderedScenes_.end(),
            [&](const std::shared_ptr<Scene> &scene) {
                return scene->getId() == sceneId;
            })
    );
    }

    std::shared_ptr<Scene> getScene(id_t sceneId)
    {
        for (const auto &it: this->orderedScenes_)
        {
            if (it.second->getId() == sceneId) {
                return it.second;
            }
        };
        return nullptr;
    }

    void update()
    {
        for (auto &scene: this->orderedScenes_) {
            scene.second->update();
        }
    }

    template<typename T>
    void update()
    {
        for (auto &scene: this->orderedScenes_) {
            scene.second->update<T>();
        }
    }
};