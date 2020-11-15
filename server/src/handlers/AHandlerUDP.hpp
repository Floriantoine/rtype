/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** AHandlerUDP
*/

#pragma once

#include "Player.hpp"
#include "Protocol.hpp"
#include "handlers/AHandler.hpp"

#include <chrono>
#include <vector>

namespace rtype::server {
    class AHandlerUDP : public AHandler {
      private:
        static constexpr long RESPONSE_DELAY = std::chrono::milliseconds(400).count();

        bool resend_(BPC::Package &package);

      protected:
        std::vector<BPC::Package> awaitingResponse_;
        std::vector<Player> &players_;

        AHandlerUDP(std::vector<Player> &players);

      public:
        ~AHandlerUDP() override = default;
        void update();
    };
}