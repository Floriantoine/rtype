/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** ShootHandler
*/

#pragma once

#include "handlers/AHandlerUDP.hpp"
#include "types.hpp"

#include <vector>

namespace rtype::client {
    class ShootHandler : public AHandlerUDP {
      public:
        struct ClientRequestBody {
            entity_id_t playerID;
        };

        struct ServerResponseBody {
            bool confirmation;
            entity_id_t missileID;
        };

        ShootHandler(GameClient &owner);
        ~ShootHandler() override = default;

      protected:
        void receiveResponse(const BPC::Package &package) override;
        void receiveRequest(const BPC::Package &package) override;
        BPC::Method getMethod() const override;
    };
}
