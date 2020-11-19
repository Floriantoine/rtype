/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Client main file
*/

#include "GameClient.hpp"
#include "engine/core/components/SpriteComponent.hpp"
#include "engine/core/components/MissileComponent.hpp"
#include "engine/core/components/BackgroundComponent.hpp"
#include "engine/core/components/CameraComponent.hpp"
#include "engine/core/components/CollideBoxComponent.hpp"
#include "engine/core/components/CollideGroupComponent.hpp"
#include "engine/core/components/HealthComponent.hpp"
#include "engine/core/components/MissileComponent.hpp"
#include "engine/core/components/PositionComponent.hpp"
#include "engine/core/components/RotationComponent.hpp"
#include "engine/core/components/SpriteComponent.hpp"

#include "game/Game.hpp"
#include "game/behaviours/BugBehaviour.hpp"
#include "game/behaviours/CameraBehaviour.hpp"
#include "game/behaviours/MissilePlayerBehaviour.hpp"
#include "game/behaviours/PataBehaviour.hpp"
#include "game/behaviours/PlayerBehaviour.hpp"
#include "game/behaviours/ButtonBehaviour.hpp"
#include "game/behaviours/TextInputBehaviour.hpp"

#include "game/components/AnimationComponent.hpp"
#include "game/components/ScaleComponent.hpp"
#include "game/components/ColorComponent.hpp"
#include "game/components/TextComponent.hpp"
#include "game/components/InputComponent.hpp"

#include "scene_loader/SceneLoader.hpp"

#include <cstdlib>
#include <exception>
#include <iostream>
#include <iterator>
#include <string>

using namespace rtype;

int init(int argc, const char **argv)
{
    client::Game::getInstance().setWindowTitle("R-Type");
    client::Game::getInstance().setVideoMode(sf::VideoMode(800, 600));

    JsonLoader::loadDefinitions("./config_file/definitions.json");

    JsonLoader::registerComponentFactory("text", client::TextComponent::factory);
    JsonLoader::registerComponentFactory("input", client::InputComponent::factory);
    JsonLoader::registerComponentFactory("color", client::ColorComponent::factory);
    JsonLoader::registerComponentFactory("animation", client::AnimationComponent::factory);
    JsonLoader::registerComponentFactory("scale", client::ScaleComponent::factory);

    JsonLoader::registerComponentFactory("player_behaviour", ABehaviourBase::getFactory<client::PlayerBehaviour>());
    JsonLoader::registerComponentFactory("missile_player_behaviour", ABehaviourBase::getFactory<client::MissilePlayerBehaviour>());
    JsonLoader::registerComponentFactory("pata_behaviour", ABehaviourBase::getFactory<client::PataBehaviour>());
    JsonLoader::registerComponentFactory("bug_behaviour", ABehaviourBase::getFactory<client::BugBehaviour>());
    JsonLoader::registerComponentFactory("camera_behaviour", ABehaviourBase::getFactory<client::CameraBehaviour>());
    JsonLoader::registerComponentFactory("button_behaviour", ABehaviourBase::getFactory<client::ButtonBehaviour>());
    JsonLoader::registerComponentFactory("text_input_behaviour", ABehaviourBase::getFactory<client::TextInputBehaviour>());

    JsonLoader::registerComponentFactory("camera", CameraComponent::factory);
    JsonLoader::registerComponentFactory("sprite", SpriteComponent::factory);
    JsonLoader::registerComponentFactory("background", BackgroundComponent::factory);
    JsonLoader::registerComponentFactory("rotation", RotationComponent::factory);
    JsonLoader::registerComponentFactory("position", PositionComponent::factory);
    JsonLoader::registerComponentFactory("collide_box", CollideBoxComponent::factory);
    JsonLoader::registerComponentFactory("collide_group", CollideGroupComponent::factory);
    JsonLoader::registerComponentFactory("health", HealthComponent::factory);
    JsonLoader::registerComponentFactory("missile", MissileComponent::factory);

    try {
        if (argc == 2)
            client::Game::getInstance().setScenesDir(argv[1]);
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
        if (argc < 2)
            return 1;
        return init(argc, argv);
        client::GameClient::Start(argc, argv);
        return 0;
    } catch (const std::exception &err) {
        std::cerr << err.what() << std::endl;
        return 1;
    }
}
