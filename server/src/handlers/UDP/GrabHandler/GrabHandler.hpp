/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** GrabHandler
*/

#pragma once

#include "Player.hpp"
#include "handlers/AHandlerUDP.hpp"
#include "types.hpp"

#include <vector>

namespace rtype::server {
    class GrabHandler : public AHandlerUDP {
      public:
        struct ServerRequestBody {
            player_id_t playerID;
            entity_id_t entityID;
            side_t side;
        };

        GrabHandler(std::vector<Player> &players);
        ~GrabHandler() override = default;

      protected:
        void response(const Network::UdpPackage &package) override;
        void request(const Network::UdpPackage &package) override;
    };
}
