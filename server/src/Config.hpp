/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Config
*/

#pragma once

#include "nlohmann/json.hpp"

#include <cstdint>

namespace rtype::server {
    /**
    * @brief data class describing the server's configuration
    */
    struct Config {
        unsigned maxGameThreads;
        uint16_t port;
    };

    /**
    * @brief nlohmann::json to rtype::server::Config class converter
    */
    void from_json(const nlohmann::json &json, Config &conf);
}
