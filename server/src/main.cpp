/*
** EPITECH PROJECT, 2020
** server
** File description:
** main
*/

#include "Config.hpp"
#include "Exception.hpp"
#include "GameServer.hpp"
#include "Server.hpp"
#include "engine/client/behaviours/MissilePlayerBehaviour.hpp"
#include "engine/client/behaviours/PataBehaviour.hpp"
#include "engine/client/behaviours/PlayerBehaviour.hpp"
#include "engine/core/components/AnimationComponent.hpp"
#include "engine/core/components/MissileComponent.hpp"
#include "engine/core/components/PositionComponent.hpp"
#include "engine/core/components/RotationComponent.hpp"
#include "engine/core/components/SpriteComponent.hpp"
#include "scene_loader/SceneLoader.hpp"

#include <fstream>
#include <iostream>

#define DEFAULT_CONFIG_FILE "r-type_server.json"

using namespace rtype;

static server::Config ParseConfig(const std::string &filePath)
{
    std::ifstream configFile(filePath.data());
    server::Config conf;

    if (!configFile.good())
        throw server::Exception("can't open config file: " + filePath);
    nlohmann::json::parse(configFile).get_to(conf);
    if (conf.maxGameThreads <= 0) {
        conf.maxGameThreads = std::thread::hardware_concurrency();
        conf.maxGameThreads -= conf.maxGameThreads != 0;
    }
    if (conf.maxGameThreads == 0)
        throw server::Exception("can't auto determine how many threads to use");
    return conf;
}

static void registerComponentFactories()
{
    JsonLoader::registerComponentFactory("sprite", SpriteComponent::factory);
    JsonLoader::registerComponentFactory("rotation", RotationComponent::factory);
    JsonLoader::registerComponentFactory("position", PositionComponent::factory);
    JsonLoader::registerComponentFactory("animation", AnimationComponent::factory);
    JsonLoader::registerComponentFactory("missile", MissileComponent::factory);
    JsonLoader::registerComponentFactory("player_script", PlayerBehaviour::getFactory<PlayerBehaviour>());
    JsonLoader::registerComponentFactory("missile_player_script", MissilePlayerBehaviour::getFactory<MissilePlayerBehaviour>());
    JsonLoader::registerComponentFactory("pata_script", PataBehaviour::getFactory<PataBehaviour>());
}

int main(int argc, const char **argv)
{
    const char *configFilePath = argc > 1 ? argv[1] : DEFAULT_CONFIG_FILE;

    try {
        server::Config conf = ParseConfig(configFilePath);
        server::GameServer::Run(conf);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
