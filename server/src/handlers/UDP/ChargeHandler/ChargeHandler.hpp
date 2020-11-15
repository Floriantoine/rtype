/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** ChargeHandler
*/

#pragma once

#include "Player.hpp"
#include "handlers/AHandlerUDP.hpp"
#include "handlers/UDP/DropHandler/DropHandler.hpp"

#include <vector>

namespace rtype::server {
    class ChargeHandler : public AHandlerUDP {
      public:
        struct ClientRequestBody {
            player_id_t playerID;
        };

        ChargeHandler(std::vector<Player> &players);
        ~ChargeHandler() override = default;

      protected:
        void response(const BPC::Package &package) override;
        void request(const BPC::Package &package) override;
    };
}
