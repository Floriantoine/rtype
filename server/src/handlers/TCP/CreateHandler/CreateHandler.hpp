/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** CreateHandler
*/

#pragma once

#include "engine/core/scene/Scene.hpp"
#include "handlers/AHandlerTCP.hpp"
#include "lobby/LobbyDispatcher.hpp"
#include "types.hpp"

#include <string>
#include <vector>

namespace rtype::server {
    class CreateHandler : public AHandlerTCP {
      public:
        struct ServerResponseBody {
            port_t port { 0 };
            lobby_id_t lobbyID = { 0 };
        };

        struct ClientRequestBody {
            std::string mapName;

            ClientRequestBody(const std::vector<unsigned char> &buffer);
        };

        CreateHandler(GameServer &owner);
        ~CreateHandler() override = default;

      protected:
        static void initScene(Scene &scene);

        void receiveResponse(const BPC::Package &package, Network::TcpSession &session) override;
        void receiveRequest(const BPC::Package &package, Network::TcpSession &session) override;
    };
}
