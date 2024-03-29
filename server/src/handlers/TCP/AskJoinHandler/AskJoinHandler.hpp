/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** AskJoinHandler
*/

#pragma once

#include "handlers/AHandlerTCP.hpp"
#include "lobby/LobbyDispatcher.hpp"
#include "types.hpp"

namespace rtype::server {
    class AskJoinHandler : public AHandlerTCP {
      public:
        struct ClientRequestBody {
            lobby_id_t lobbyID;
        };

        struct ServerResponseBody {
            port_t port;
        };

        AskJoinHandler(GameServer &owner);
        ~AskJoinHandler() override = default;

      protected:
        void receiveResponse(const BPC::Package &package, Network::TcpSession &session) override;
        void receiveRequest(const BPC::Package &package, Network::TcpSession &session) override;
    };
}
