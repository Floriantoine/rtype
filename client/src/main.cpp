/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Client main file
*/

#include "GameClient.hpp"
#include "engine/core/components/SpriteComponent.hpp"
#include "engine/core/components/MissileComponent.hpp"
#include "engine/core/components/AnimationComponent.hpp"
#include "engine/core/components/BackgroundComponent.hpp"
#include "engine/core/components/CameraComponent.hpp"
#include "engine/core/components/CollideBoxComponent.hpp"
#include "engine/core/components/CollideGroupComponent.hpp"
#include "engine/core/components/HealthComponent.hpp"
#include "engine/core/components/MissileComponent.hpp"
#include "engine/core/components/PositionComponent.hpp"
#include "engine/core/components/RotationComponent.hpp"
#include "engine/core/components/SpriteComponent.hpp"
#include "engine/core/systems/BehaviourSystem.hpp"
#include "engine/core/systems/CameraSystem.hpp"
#include "engine/core/systems/CollisionSystem.hpp"
#include "engine/core/systems/HealthSystem.hpp"
#include "game/Game.hpp"
#include "game/behaviours/BugBehaviour.hpp"
#include "game/behaviours/CameraBehaviour.hpp"
#include "game/behaviours/MissilePlayerBehaviour.hpp"
#include "game/behaviours/PataBehaviour.hpp"
#include "game/behaviours/PlayerBehaviour.hpp"
#include "game/systems/AnimationSystem.hpp"
#include "game/systems/EventSystem.hpp"
#include "game/systems/SpriteSystem.hpp"
#include "game/systems/BackgroundSystem.hpp"
#include "scene_loader/SceneLoader.hpp"

#include <cstdlib>
#include <exception>
#include <iostream>
#include <iterator>
#include <string>

using namespace rtype;
using namespace rtype::client;

int init()
{
    Game::getInstance().setWindowTitle("R-Type");
    Game::getInstance().setVideoMode(sf::VideoMode(800, 600));

    JsonLoader::loadDefinitions("./config_file/definitions.json");

    JsonLoader::registerComponentFactory("camera", CameraComponent::factory);
    JsonLoader::registerComponentFactory("sprite", SpriteComponent::factory);
    JsonLoader::registerComponentFactory("background", BackgroundComponent::factory);
    JsonLoader::registerComponentFactory("rotation", RotationComponent::factory);
    JsonLoader::registerComponentFactory("position", PositionComponent::factory);
    JsonLoader::registerComponentFactory("collide_box", CollideBoxComponent::factory);
    JsonLoader::registerComponentFactory("collide_group", CollideGroupComponent::factory);
    JsonLoader::registerComponentFactory("health", HealthComponent::factory);
    JsonLoader::registerComponentFactory("animation", AnimationComponent::factory);
    JsonLoader::registerComponentFactory("missile", MissileComponent::factory);
    JsonLoader::registerComponentFactory("player_behaviour", ABehaviour::getFactory<PlayerBehaviour>());
    JsonLoader::registerComponentFactory("missile_player_behaviour", ABehaviour::getFactory<MissilePlayerBehaviour>());
    JsonLoader::registerComponentFactory("pata_behaviour", ABehaviour::getFactory<PataBehaviour>());
    JsonLoader::registerComponentFactory("bug_behaviour", ABehaviour::getFactory<BugBehaviour>());
    JsonLoader::registerComponentFactory("camera_behaviour", ABehaviourBase::getFactory<CameraBehaviour>());

    try {
        auto scene = JsonLoader::createScene(Game::getInstance(), "./config_file/scene/stage1.json");

        scene->createSystem<rtype::CameraSystem>();
        scene->createSystem<EventSystem>();
        scene->createSystem<rtype::BehaviourSystem>();
        scene->createSystem<AnimationSystem>();
        scene->createSystem<SpriteSystem>();
        scene->createSystem<BackgroundSystem>();
        scene->createSystem<CollisionSystem>();
        scene->createSystem<HealthSystem>();

        Game::getInstance().start();
        return 0;
    } catch (const Exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

int main(const int argc, const char **argv)
{
    return init();

    try {
        GameClient::Start(argc, argv);
        return 0;
    } catch (const std::exception &err) {
        std::cerr << err.what() << std::endl;
        return 1;
    }
}
