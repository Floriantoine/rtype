/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Config
*/

#include "Config.hpp"

namespace rtype::server {
    void from_json(const nlohmann::json &json, Config &conf)
    {
        json.at("port").get_to(conf.port);
        try {
            json.at("maxGameThreads").get_to(conf.maxGameThreads);
        } catch (const nlohmann::json::exception &e) {
            conf.maxGameThreads = 0;
        }
    }
}