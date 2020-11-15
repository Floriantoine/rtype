/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** AskJoinHandler
*/

#pragma once

#include "handlers/AHandler.hpp"
#include "types.hpp"

namespace rtype::server {
    class AskJoinHandler : public AHandler {
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
        void response(const BPC::Package &package) override;
        void request(const BPC::Package &package) override;
    };
}
