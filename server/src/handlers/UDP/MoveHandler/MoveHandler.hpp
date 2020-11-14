/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** MoveHandler
*/

#pragma once

#include "handlers/IHandler.hpp"

namespace rtype {
    class MoveHandler : public IHandler {
      public:
        MoveHandler() = default;
        ~MoveHandler() override = default;

      protected:
        void response(char *body) override;
        void request(char *body) override;
    };
}
