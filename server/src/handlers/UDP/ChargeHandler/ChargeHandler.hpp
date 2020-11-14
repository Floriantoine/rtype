/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** ChargeHandler
*/

#pragma once

#include "handlers/IHandler.hpp"

namespace rtype {
    class ChargeHandler : public IHandler {
      public:
        ChargeHandler() = default;
        ~ChargeHandler() override = default;

      protected:
        void response(char *body) override;
        void request(char *body) override;
    };
}
