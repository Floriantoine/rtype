/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** LeaveHandler
*/

#pragma once

#include "handlers/IHandler.hpp"

namespace rtype {
    class LeaveHandler : public IHandler {
      public:
        LeaveHandler() = default;
        ~LeaveHandler() override = default;

      protected:
        void response(char *body) override;
        void request(char *body) override;
    };
}
