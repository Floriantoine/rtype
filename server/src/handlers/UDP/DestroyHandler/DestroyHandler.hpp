/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** DestroyHandler
*/

#pragma once

#include "handlers/IHandler.hpp"

namespace rtype {
    class DestroyHandler : public IHandler {
      public:
        DestroyHandler() = default;
        ~DestroyHandler() override = default;

      protected:
        void response(char *body) override;
        void request(char *body) override;
    };
}
