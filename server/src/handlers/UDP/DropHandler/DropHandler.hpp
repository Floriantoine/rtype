/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** DropHandler
*/

#pragma once

#include "Player.hpp"
#include "handlers/AHandlerUDP.hpp"
#include "types.hpp"

#include <vector>

namespace rtype::server {
    class DropHandler : public AHandlerUDP {
      public:
        struct ServerRequestBody {
            player_id_t playerID;
        };

        struct ClientRequestBody {
            player_id_t playerID;
        };

        DropHandler(std::vector<Player> &players);
        ~DropHandler() override = default;

      protected:
        void response(const Network::UdpPackage &package) override;
        void request(const Network::UdpPackage &package) override;
    };
}
