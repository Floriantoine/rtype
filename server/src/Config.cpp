/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Config
*/

#include "Config.hpp"

namespace RType {
    void from_json(const nlohmann::json &json, Config &conf)
    {
        json.at("port").get_to(conf.port);
        try {
            json.at("maxThreads").get_to(conf.maxThreads);
        } catch (const nlohmann::json::exception &e) {
            conf.maxThreads = 0;
        }
    }
}