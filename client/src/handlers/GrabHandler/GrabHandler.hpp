/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** GrabHandler
*/

#pragma once

#include "handlers/AHandlerUDP.hpp"
#include "types.hpp"

#include <vector>

namespace rtype::client {
    class GrabHandler : public AHandlerUDP {
      public:
        struct ServerRequestBody {
            entity_id_t playerID;
            entity_id_t entityID;
            side_t side;
        };

        GrabHandler(GameClient &owner);
        ~GrabHandler() override = default;

      protected:
        void receiveResponse(const BPC::Package &package) override;
        void receiveRequest(const BPC::Package &package) override;
        BPC::Method getMethod() const override;
    };
}
