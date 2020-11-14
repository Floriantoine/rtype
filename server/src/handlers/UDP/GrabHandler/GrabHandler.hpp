/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** GrabHandler
*/

#pragma once

#include "handlers/IHandler.hpp"

namespace rtype {
    class GrabHandler : public IHandler {
      public:
        GrabHandler() = default;
        ~GrabHandler() override = default;

      protected:
        void response(char *body) override;
        void request(char *body) override;
    };
}
