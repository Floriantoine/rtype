/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** PositionHandler
*/

#pragma once

#include "Player.hpp"
#include "handlers/AHandlerUDP.hpp"
#include "types.hpp"

#include <sys/types.h>
#include <vector>

namespace rtype::server {
    class PositionHandler : public AHandlerUDP {
      public:
        struct ServerRequestBody {
            entity_id_t entityID;
            coordinate_t x;
            coordinate_t y;
        };

        PositionHandler(std::vector<Player> &players);
        ~PositionHandler() override = default;

      protected:
        void response(const Network::UdpPackage &package) override;
        void request(const Network::UdpPackage &package) override;
    };
}
