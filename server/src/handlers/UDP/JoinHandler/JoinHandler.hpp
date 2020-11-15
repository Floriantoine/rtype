/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** JoinHandler
*/

#pragma once

#include "Player.hpp"
#include "handlers/AHandlerUDP.hpp"
#include "types.hpp"

#include <vector>

namespace rtype::server {
    class JoinHandler : public AHandlerUDP {
      public:
        struct ServerRequestBody {
            player_id_t playerID;
            std::vector<unsigned char> mapName;
        };

        JoinHandler(std::vector<Player> &players);
        ~JoinHandler() override = default;

      protected:
        void response(const BPC::Package &package) override;
        void request(const BPC::Package &package) override;
    };
}
