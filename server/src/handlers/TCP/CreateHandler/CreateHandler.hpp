/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** CreateHandler
*/

#pragma once

#include "handlers/IHandler.hpp"

namespace rtype {
    class CreateHandler : public IHandler {
      public:
        CreateHandler() = default;
        ~CreateHandler() override = default;

      protected:
        void response(char *body) override;
        void request(char *body) override;
    };
}
