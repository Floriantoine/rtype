/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** ShootHandler
*/

#pragma once

#include "handlers/IHandler.hpp"
#include "types.hpp"

namespace rtype {
    class ShootHandler : public IHandler {
      public:
        struct ClientRequestBody {
            player_id_t playerID;
        };

        ShootHandler() = default;
        ~ShootHandler() override = default;

      protected:
        void response(char *body) override;
        void request(char *body) override;
    };
}
