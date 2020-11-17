/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Client main file
*/

#include "GameClient.hpp"
#include "engine/client/Game.hpp"
#include "engine/client/behaviours/BugBehaviour.hpp"
#include "engine/client/behaviours/MissilePlayerBehaviour.hpp"
#include "engine/client/behaviours/PataBehaviour.hpp"
#include "engine/client/behaviours/PlayerBehaviour.hpp"
#include "engine/client/systems/AnimationSystem.hpp"
#include "engine/client/systems/BackgroundSystem.hpp"
#include "engine/client/systems/SpriteSystem.hpp"
#include "engine/core/components/AnimationComponent.hpp"
#include "engine/core/components/BackgroundComponent.hpp"
#include "engine/core/components/CollideBoxComponent.hpp"
#include "engine/core/components/CollideGroupComponent.hpp"
#include "engine/core/components/HealthComponent.hpp"
#include "engine/core/components/MissileComponent.hpp"
#include "engine/core/components/PositionComponent.hpp"
#include "engine/core/components/RotationComponent.hpp"
#include "engine/core/components/SpriteComponent.hpp"
#include "engine/core/ecs/component/Component.hpp"
#include "engine/core/systems/BehaviourSystem.hpp"
#include "engine/core/systems/CollisionSystem.hpp"
#include "engine/core/systems/EventSystem.hpp"
#include "engine/core/systems/HealthSystem.hpp"
#include "scene_loader/SceneLoader.hpp"

#include <cstdlib>
#include <exception>
#include <iostream>
#include <iterator>
#include <string>

using namespace rtype;

int init()
{
    client::Game::getInstance().setWindowTitle("R-Type");
    client::Game::getInstance().setVideoMode(sf::VideoMode(800, 600));

    JsonLoader::loadDefinitions("./config_file/definitions.json");

    JsonLoader::registerComponentFactory("sprite", SpriteComponent::factory);
    JsonLoader::registerComponentFactory("background", BackgroundComponent::factory);
    JsonLoader::registerComponentFactory("rotation", RotationComponent::factory);
    JsonLoader::registerComponentFactory("position", PositionComponent::factory);
    JsonLoader::registerComponentFactory("collide_box", CollideBoxComponent::factory);
    JsonLoader::registerComponentFactory("collide_group", CollideGroupComponent::factory);
    JsonLoader::registerComponentFactory("health", HealthComponent::factory);
    JsonLoader::registerComponentFactory("animation", AnimationComponent::factory);
    JsonLoader::registerComponentFactory("missile", MissileComponent::factory);
    JsonLoader::registerComponentFactory("player_script", PlayerBehaviour::getFactory<PlayerBehaviour>());
    JsonLoader::registerComponentFactory("missile_player_script", MissilePlayerBehaviour::getFactory<MissilePlayerBehaviour>());
    JsonLoader::registerComponentFactory("pata_script", PataBehaviour::getFactory<PataBehaviour>());
    JsonLoader::registerComponentFactory("bug_script", BugBehaviour::getFactory<BugBehaviour>());

    try {
        auto scene = JsonLoader::createScene(client::Game::getInstance(), "./config_file/scene/stage1.json");

        scene->createSystem<EventSystem>();
        scene->createSystem<BehaviourSystem>();
        scene->createSystem<client::AnimationSystem>();
        scene->createSystem<client::SpriteSystem>();
        scene->createSystem<client::BackgroundSystem>();
        scene->createSystem<CollisionSystem>();
        scene->createSystem<HealthSystem>();

        client::Game::getInstance().start();
        return 0;
    } catch (const Exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

int main(const int argc, const char **argv)
{
    try {
        client::GameClient::Start(argc, argv);
        return 0;
    } catch (const std::exception &err) {
        std::cerr << err.what() << std::endl;
        return 1;
    }
}
