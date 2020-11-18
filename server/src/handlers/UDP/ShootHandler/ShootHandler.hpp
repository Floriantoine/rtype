/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** ShootHandler
*/

#pragma once

#include "Player.hpp"
#include "handlers/AHandlerUDP.hpp"
#include "types.hpp"

#include <vector>

namespace rtype::server {
    class ShootHandler : public AHandlerUDP {
      public:
        struct ClientRequestBody {
            entity_id_t playerID;
        };

        struct ServerResponseBody {
            bool confirmation;
            entity_id_t missileID;
        };

        ShootHandler(Lobby &owner);
        ~ShootHandler() override = default;

      protected:
        void receiveResponse(const Network::UdpPackage &package) override;
        void receiveRequest(const Network::UdpPackage &package) override;
        BPC::Method getMethod() const override;
    };
}
