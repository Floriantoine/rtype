/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Player
*/

#pragma once

#include "boost/asio/ip/udp.hpp"
#include "types.hpp"
#include "core/Protocol.hpp"

namespace rtype::server {
    struct Player {
        player_id_t id;
        boost::asio::ip::udp::endpoint endpoint;
        long lastReception;
    };
}
