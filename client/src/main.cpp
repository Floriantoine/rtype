/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Client main file
*/

#include "engine/client/Game.hpp"
#include "scene_loader/SceneLoader.hpp"
#include "engine/core/ecs/component/Component.hpp"
#include "engine/core/components/AnimationComponent.hpp"
#include "engine/core/components/MissileComponent.hpp"
#include "engine/core/components/PositionComponent.hpp"
#include "engine/core/components/RotationComponent.hpp"
#include "engine/core/components/TextureComponent.hpp"
#include "engine/core/components/PlayerScriptComponent.hpp"
#include "engine/core/components/PositionComponent.hpp"
#include "engine/core/systems/ScriptSystem.hpp"

#include <iostream>

using namespace rtype;
using namespace rtype::client;

std::unordered_map<std::string, SceneLoader::component_factory_t> SceneLoader::ComponentFactory_;

int main()
{
    Game game;
    SceneLoader sceneLoader = SceneLoader("./scene/stage1.json");

    sceneLoader.AddComponentFactory("texture", TextureComponent::factory);
    sceneLoader.AddComponentFactory("rotation", RotationComponent::factory);
    sceneLoader.AddComponentFactory("position", PositionComponent::factory);
    sceneLoader.AddComponentFactory("animation", AnimationComponent::factory);
    sceneLoader.AddComponentFactory("missile", MissileComponent::factory);
    sceneLoader.AddComponentFactory("player_script", PlayerScriptComponent::getFactory<PlayerScriptComponent>());

    auto scene = sceneLoader.load(game);

    scene->createSystem<ScriptSystem>();

    game.start();
    return 0;
}
