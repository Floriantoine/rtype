/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Client main file
*/
#include "../deps/engine/client/Game.hpp"
#include "../deps/engine/core/components/AnimationComponent.hpp"
#include "../deps/engine/core/components/MissileComponent.hpp"
#include "../deps/engine/core/components/PositionComponent.hpp"
#include "../deps/engine/core/components/RotationComponent.hpp"
#include "../deps/engine/core/components/TextureComponent.hpp"
#include "../deps/scene_loader/SceneLoader.hpp"
#include "engine/core/ecs/component/Component.hpp"
#include "engine/core/ecs/system/ASystem.hpp"

#include <iostream>

using namespace rtype;
using namespace rtype::client;

// class PositionComponent : public Component<PositionComponent> {
//   public:
//     int x { 0 };
//     int y { 0 };

//     PositionComponent() = default;
//     PositionComponent(int x, int y)
//         : x { x }
//         , y { y }
//     { }
// };

std::unordered_map<std::string, SceneLoader::component_factory_t> SceneLoader::ComponentFactory_;

class ARenderSystem : public ASystem {
  protected:
    ARenderSystem()
        : ASystem(ASystem::RENDER_SYSTEM_GROUP)
    { }
};

class SpriteSystem : public ARenderSystem {
    void update(long elapsedTime) override
    {
    }
};

class PositionSystem : public ASystem {
  public:
    void update(long elapsedTime) override
    {
    }
};

int main(int ac, char *av[])
{
    Game game;
    SceneLoader sceneLoader = SceneLoader("./scene/stage1.json");

    sceneLoader.AddComponentFactory("texture", TextureComponent::factory);
    sceneLoader.AddComponentFactory("rotation", RotationComponent::factory);
    sceneLoader.AddComponentFactory("position", PositionComponent::factory);
    sceneLoader.AddComponentFactory("animation", AnimationComponent::factory);
    sceneLoader.AddComponentFactory("missile", MissileComponent::factory);

    auto scene = sceneLoader.load(game);

    game.start();
    return 0;
}
