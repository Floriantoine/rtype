/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Config
*/

#pragma once

#include "nlohmann/json.hpp"

#include <cstdint>

namespace RType {
    struct Config {
        unsigned maxThreads;
        uint16_t port;
    };

    void from_json(const nlohmann::json &json, Config &conf);
}
