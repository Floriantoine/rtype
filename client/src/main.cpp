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
#include "engine/core/components/SpriteComponent.hpp"
#include "engine/core/components/PlayerScriptComponent.hpp"
#include "engine/core/components/PataScriptComponent.hpp"
#include "engine/core/components/PositionComponent.hpp"
#include "engine/client/systems/AnimationSystem.hpp"
#include "engine/core/systems/ScriptSystem.hpp"
#include "engine/core/systems/EventSystem.hpp"

#include <iostream>

using namespace rtype;
using namespace rtype::client;

int main()
{
    Game::getInstance().setWindowTitle("R-Type");
    Game::getInstance().setVideoMode(sf::VideoMode(800, 600));

    JsonLoader::loadDefinitions("./config_file/definitions.json");

    JsonLoader::registerComponentFactory("sprite", SpriteComponent::factory);
    JsonLoader::registerComponentFactory("rotation", RotationComponent::factory);
    JsonLoader::registerComponentFactory("position", PositionComponent::factory);
    JsonLoader::registerComponentFactory("animation", AnimationComponent::factory);
    JsonLoader::registerComponentFactory("missile", MissileComponent::factory);
    // JsonLoader::registerComponentFactory("player_script", PlayerScriptComponent::getFactory<PlayerScriptComponent>());
    JsonLoader::registerComponentFactory("pata_script", PataScriptComponent::getFactory<PataScriptComponent>());

    auto scene = JsonLoader::createScene(Game::getInstance(), "./config_file/scene/stage1.json");

    scene->createSystem<EventSystem>();
    scene->createSystem<ScriptSystem>();
    scene->createSystem<AnimationSystem>();

    Game::getInstance().start();
    return 0;
}
