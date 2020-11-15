/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** CreateHandler
*/

#pragma once

#include "handlers/AHandler.hpp"
#include "types.hpp"

#include <string>
#include <vector>

namespace rtype::server {
    class CreateHandler : public AHandler {
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
        void response(const BPC::Package &package) override;
        void request(const BPC::Package &package) override;
    };
}
