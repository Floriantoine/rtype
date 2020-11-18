/*
** EPITECH PROJECT, 2020
** client
** File description:
** GameStateHandler
*/

#pragma once

#include "handlers/AHandlerUDP.hpp"
#include "types.hpp"

namespace rtype::client {
    class GameStateHandler : public AHandlerUDP {
      public:
        GameStateHandler(GameClient &owner);
        ~GameStateHandler() noexcept override = default;
        struct ClientRequestBody {
            GameState state;
        };

        struct ServerRequestBody {
            GameState state;
        };
        

      private:
        void receiveRequest(const BPC::Package &package) override;
        void receiveResponse(const BPC::Package &package) override;
        BPC::Method getMethod() const override;
    };
};
