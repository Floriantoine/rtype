/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** GameClient
*/

#pragma once

#include "Client.hpp"
#include "Protocol.hpp"
#include "types.hpp"

#include <memory>

namespace rtype::client {
    class GameClient {
      private:
        boost::asio::io_context io_context_;
        std::shared_ptr<Network::UdpClient> conn_;

        GameClient(const int argc, const char **argv);
        port_t connectToLobby_(const char *ip, port_t port, const BPC::Package &package);
        BPC::Package getInitialPackage_(const int argc, const char **argv);

      public:
        ~GameClient() = default;
        static void Start(const int argc, const char **argv);
    };
}
