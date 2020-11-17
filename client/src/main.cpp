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
#include "engine/core/components/CollideBoxComponent.hpp"
#include "engine/core/components/CollideGroupComponent.hpp"
#include "engine/client/behaviours/MissilePlayerBehaviour.hpp"
#include "engine/client/behaviours/PlayerBehaviour.hpp"
#include "engine/client/behaviours/PataBehaviour.hpp"
#include "engine/core/components/PositionComponent.hpp"
#include "engine/client/systems/AnimationSystem.hpp"
#include "engine/client/systems/SpriteSystem.hpp"
#include "engine/client/systems/SpriteSystem.hpp"
#include "engine/core/systems/BehaviourSystem.hpp"
#include "engine/core/systems/EventSystem.hpp"
#include "engine/core/systems/CollisionSystem.hpp"

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
    JsonLoader::registerComponentFactory("collide_box", CollideBoxComponent::factory);
    JsonLoader::registerComponentFactory("collide_group", CollideGroupComponent::factory);
    JsonLoader::registerComponentFactory("animation", AnimationComponent::factory);
    JsonLoader::registerComponentFactory("missile", MissileComponent::factory);
    JsonLoader::registerComponentFactory("player_script", PlayerBehaviour::getFactory<PlayerBehaviour>());
    JsonLoader::registerComponentFactory("missile_player_script", MissilePlayerBehaviour::getFactory<MissilePlayerBehaviour>());
    JsonLoader::registerComponentFactory("pata_script", PataBehaviour::getFactory<PataBehaviour>());

    try {
        auto scene = JsonLoader::createScene(Game::getInstance(), "./config_file/scene/stage1.json");
        
        scene->createSystem<EventSystem>();
        scene->createSystem<BehaviourSystem>();
        scene->createSystem<AnimationSystem>();
        scene->createSystem<SpriteSystem>();
        scene->createSystem<CollisionSystem>();

        Game::getInstance().start();
        return 0;
    } catch (const Exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
