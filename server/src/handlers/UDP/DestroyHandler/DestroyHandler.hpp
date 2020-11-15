/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** DestroyHandler
*/

#pragma once

#include "Player.hpp"
#include "handlers/AHandlerUDP.hpp"
#include "types.hpp"

#include <vector>

namespace rtype::server {
    class DestroyHandler : public AHandlerUDP {
      public:
        struct ServerRequestBody {
            entity_id_t entityID;
        };

        DestroyHandler(std::vector<Player> &players);
        ~DestroyHandler() override = default;

      protected:
        void response(const BPC::Package &package) override;
        void request(const BPC::Package &package) override;
    };
}
