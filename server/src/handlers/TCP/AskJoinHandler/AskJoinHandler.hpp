/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** AskJoinHandler
*/

#pragma once

#include "handlers/IHandler.hpp"
#include "types.hpp"

namespace rtype {
    class AskJoinHandler : public IHandler {
      public:
        struct ClientRequestBody {
            lobby_id_t lobbyID;
        };

        struct ServerResponseBody {
            port_t port;
        };

        AskJoinHandler() = default;
        ~AskJoinHandler() override = default;

      protected:
        void response(char *body) override;
        void request(char *body) override;
    };
}
