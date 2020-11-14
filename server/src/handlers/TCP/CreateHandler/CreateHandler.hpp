/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** CreateHandler
*/

#pragma once

#include "handlers/IHandler.hpp"
#include "handlers/TCP/AskJoinHandler/AskJoinHandler.hpp"

#include <string>
#include <vector>

namespace rtype {
    class CreateHandler : public IHandler {
      public:
        struct ServerResponseBody {
            port_t port;
        };
        struct ClientRequestBody {
            std::string mapName;

            ClientRequestBody(std::vector<unsigned char> buffer);
        };

        CreateHandler() = default;
        ~CreateHandler() override = default;

      protected:
        void response(char *body) override;
        void request(char *body) override;
    };
}
