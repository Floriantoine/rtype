/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** HitHandler
*/

#pragma once

#include "handlers/IHandler.hpp"
#include "types.hpp"

namespace rtype {
    class HitHandler : public IHandler {
      public:
        struct ServerRequestBody {
            entity_id_t entity;
        };

        HitHandler() = default;
        ~HitHandler() override = default;

      protected:
        void response(const BPC::Package &package) override;
        void request(const BPC::Package &package) override;
    };
}
