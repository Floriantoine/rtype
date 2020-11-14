/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** SpawnHandler
*/

#pragma once

#include "handlers/IHandler.hpp"
#include "types.hpp"

namespace rtype {
    class SpawnHandler : public IHandler {
      public:
        struct ServerRequestBody {
            entity_id_t entityID;
        };

        SpawnHandler() = default;
        ~SpawnHandler() override = default;

      protected:
        void response(char *body) override;
        void request(char *body) override;
    };
}
