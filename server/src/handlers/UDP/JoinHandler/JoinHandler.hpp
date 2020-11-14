/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** JoinHandler
*/

#pragma once

#include "handlers/IHandler.hpp"

namespace rtype {
    class JoinHandler : public IHandler {
      public:
        JoinHandler() = default;
        ~JoinHandler() override = default;

      protected:
        void response(char *body) override;
        void request(char *body) override;
    };
}
