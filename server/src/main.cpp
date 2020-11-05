/*
** EPITECH PROJECT, 2020
** server
** File description:
** main
*/
#include "Config.hpp"
#include "Server.hpp"
#include "utils/Exception.hpp"

#include <exception>
#include <fstream>
#include <iostream>

#define DEFAULT_CONFIG_FILE "r-type_server.json"

static RType::Config parseConfig(const std::string &filePath)
{
    std::ifstream configFile(filePath.data());
    RType::Config conf;

    if (!configFile.good())
        throw RType::Exception("Can't open config file: " + filePath);
    nlohmann::json::parse(configFile).get_to(conf);
    if (conf.maxThreads <= 0)
        conf.maxThreads = std::thread::hardware_concurrency();
    if (conf.maxThreads == 0)
        throw RType::Exception("Can't auto determine how many threads to use");
    conf.maxThreads -= conf.maxThreads != 0;
    return conf;
}

int main(int argc, const char **argv)
{
    const char *configFilePath = argc > 1 ? argv[1] : DEFAULT_CONFIG_FILE;

    try {
        RType::Config conf = parseConfig(configFilePath);
        RType::Server::run(conf);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
