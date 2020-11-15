/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** MoveHandler
*/

#pragma once

#include "handlers/IHandler.hpp"
#include "types.hpp"

#include <sys/types.h>

namespace rtype {
    class MoveHandler : public IHandler {
      public:
        struct ServerRequestBody {
            entity_id_t entityID;
            coordinate_t x;
            coordinate_t y;
        };

        struct ClientRequestBody {
            player_id_t playerID;
            direction_t direction;
        };

        MoveHandler() = default;
        ~MoveHandler() override = default;

      protected:
        void response(const BPC::Package &package) override;
        void request(const BPC::Package &package) override;
    };
}
