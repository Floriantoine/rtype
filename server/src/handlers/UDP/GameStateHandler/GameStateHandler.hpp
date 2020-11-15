/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** GameStateHandler
*/

#pragma once

#include "Player.hpp"
#include "handlers/AHandlerUDP.hpp"
#include "types.hpp"

#include <vector>

namespace rtype::server {
    class GameStateHandler : public AHandlerUDP {
      public:
        struct ClientRequestBody {
            game_state_t state;
        };

        struct ServerRequestBody {
            game_state_t state;
        };

        GameStateHandler(std::vector<Player> &players);
        ~GameStateHandler() override = default;

      protected:
        void response(const Network::UdpPackage &package) override;
        void request(const Network::UdpPackage &package) override;
    };
}
