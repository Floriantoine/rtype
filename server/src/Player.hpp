/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Player
*/

#pragma once

#include "types.hpp"
#include "core/Protocol.hpp"

namespace rtype::server {
    struct Player {
        player_id_t id;
        BPC::Endpoint endpoint;
        long lastReception;
    };
}
