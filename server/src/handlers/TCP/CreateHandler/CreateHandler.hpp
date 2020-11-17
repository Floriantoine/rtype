/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** CreateHandler
*/

#pragma once

#include "handlers/AHandlerTCP.hpp"
#include "lobby/LobbyDispatcher.hpp"
#include "types.hpp"

#include <string>
#include <vector>

namespace rtype::server {
    class CreateHandler : public AHandlerTCP {
      public:
        struct ServerResponseBody {
            port_t port;
        };

        struct ClientRequestBody {
            std::string mapName;

            ClientRequestBody(const std::vector<unsigned char> &buffer);
        };

        CreateHandler(LobbyDispatcher &dispatcher);
        ~CreateHandler() override = default;

      protected:
        void response(const BPC::Package &package, Network::TcpSession &session) override;
        void request(const BPC::Package &package, Network::TcpSession &session) override;
    };
}
