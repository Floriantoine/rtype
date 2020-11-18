/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** DropHandler
*/

#pragma once

#include "handlers/AHandlerUDP.hpp"
#include "types.hpp"

namespace rtype::client {
    class DropHandler : public AHandlerUDP {
      public:
        struct ServerRequestBody {
            entity_id_t playerID;
        };

        struct ClientRequestBody {
            entity_id_t playerID;
        };

        DropHandler(GameClient &owner);
        ~DropHandler() override = default;

      protected:
        void receiveResponse(const BPC::Package &package) override;
        void receiveRequest(const BPC::Package &package) override;
        BPC::Method getMethod() const override;
    };
}
