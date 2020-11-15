/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** GrabHandler
*/

#pragma once

#include "handlers/IHandler.hpp"
#include "types.hpp"

namespace rtype {
    class GrabHandler : public IHandler {
      public:
        struct ServerRequestBody {
            player_id_t playerID;
            entity_id_t entityID;
            side_t side;
        };

        GrabHandler() = default;
        ~GrabHandler() override = default;

      protected:
        void response(const BPC::Package &package) override;
        void request(const BPC::Package &package) override;
    };
}
