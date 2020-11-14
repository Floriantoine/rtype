/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** GameStateHandler
*/

#pragma once

#include "handlers/IHandler.hpp"
#include "types.hpp"

namespace rtype {
    class GameStateHandler : public IHandler {
      public:
        struct ClientRequestBody {
            game_state_t state;
        };

        struct ServerRequestBody {
            game_state_t state;
        };

        GameStateHandler() = default;
        ~GameStateHandler() override = default;

      protected:
        void response(char *body) override;
        void request(char *body) override;
    };
}
