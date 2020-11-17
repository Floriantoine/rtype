/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** AHandlerTCP
*/

#pragma once

#include "Server.hpp"

namespace rtype::server {
    class GameServer;

    class AHandlerTCP {
      protected:
        GameServer &owner_;

        AHandlerTCP(GameServer &owner);

        virtual void receiveRequest(const BPC::Package &package, Network::TcpSession &client) = 0;
        virtual void receiveResponse(const BPC::Package &package, Network::TcpSession &client) = 0;

      public:
        static void unknowPacket(const BPC::Package &package, Network::TcpSession &client);

        virtual ~AHandlerTCP() = default;
        void receive(const BPC::Package &package, Network::TcpSession &client);
    };
}
