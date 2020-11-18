/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** MoveHandler
*/

#pragma once

#include "handlers/AHandlerUDP.hpp"
#include "types.hpp"

#include <sys/types.h>
#include <vector>

namespace rtype::client {
    class MoveHandler : public AHandlerUDP {
      public:
        struct ClientRequestBody {
            entity_id_t playerID;
            Direction direction;
            bool state;
        };

        MoveHandler(GameClient &owner);
        ~MoveHandler() override = default;

      protected:
        void receiveResponse(const BPC::Package &package) override;
        void receiveRequest(const BPC::Package &package) override;
        BPC::Method getMethod() const override;
    };
}
