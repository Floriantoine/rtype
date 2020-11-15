/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** ChargeHandler
*/

#pragma once

#include "handlers/IHandler.hpp"
#include "handlers/UDP/DropHandler/DropHandler.hpp"

namespace rtype {
    class ChargeHandler : public IHandler {
      public:
        struct ClientRequestBody {
            player_id_t playerID;
        };

        ChargeHandler() = default;
        ~ChargeHandler() override = default;

      protected:
        void response(const BPC::Package &package) override;
        void request(const BPC::Package &package) override;
    };
}
