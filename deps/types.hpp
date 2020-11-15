/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** types
*/

#pragma once

#include <sys/types.h>

namespace rtype {
    typedef size_t entity_id_t;
    typedef ssize_t coordinate_t;
    typedef char lobby_id_t[6];
    typedef unsigned short port_t;
    typedef unsigned char game_state_t;
    typedef unsigned char player_id_t;
    typedef unsigned char direction_t;
    typedef unsigned char side_t;

    enum class Side : side_t {
        FRONT = 0,
        BACK = 1
    };

    enum class Direction : direction_t {
        UP = 1,
        DOWN = UP << 1,
        LEFT = DOWN << 1,
        RIGHT = LEFT << 1
    };

    enum class GameState : game_state_t {
        AWT_START,
        START,
        PAUSE,
        WIN,
        LOSE,
    };
}
