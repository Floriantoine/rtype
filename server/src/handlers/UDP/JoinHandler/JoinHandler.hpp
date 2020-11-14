/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** JoinHandler
*/

#pragma once

#include "handlers/IHandler.hpp"
#include "types.hpp"

#include <vector>

namespace rtype {
    class JoinHandler : public IHandler {
      public:
        struct ServerRequestBody {
            player_id_t playerID;
            std::vector<unsigned char> mapName;
        };

        JoinHandler() = default;
        ~JoinHandler() override = default;

      protected:
        void response(char *body) override;
        void request(char *body) override;
    };
}
