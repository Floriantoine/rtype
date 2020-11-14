/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** DropHandler
*/

#pragma once

#include "handlers/IHandler.hpp"
#include "types.hpp"

namespace rtype {
    class DropHandler : public IHandler {
      public:
        struct ServerRequestBody {
            player_id_t playerID;
        };

        struct ClientRequestBody {
            player_id_t playerID;
        };

        DropHandler() = default;
        ~DropHandler() override = default;

      protected:
        void response(char *body) override;
        void request(char *body) override;
    };
}
