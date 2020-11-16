/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** MoveHandler
*/

#pragma once

#include "Player.hpp"
#include "handlers/AHandlerUDP.hpp"
#include "types.hpp"

#include <sys/types.h>
#include <vector>

namespace rtype::server {
    class MoveHandler : public AHandlerUDP {
      public:
        struct ServerRequestBody {
            entity_id_t entityID;
            coordinate_t x;
            coordinate_t y;
        };

        struct ClientRequestBody {
            player_id_t playerID;
            direction_t direction;
        };

        MoveHandler(std::vector<Player> &players);
        ~MoveHandler() override = default;

      protected:
        void response(const Network::UdpPackage &package) override;
        void request(const Network::UdpPackage &package) override;
    };
}
