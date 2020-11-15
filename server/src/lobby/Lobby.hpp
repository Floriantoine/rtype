/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Lobby
*/

#pragma once

#include "Server.hpp"
#include "handlers/IHandler.hpp"

#include <memory>
#include <string>
#include <unordered_map>

namespace rtype::server {
    /**
    * @brief representation of a lobby, where the game logic is processed
    */
    class Lobby {
      private:
        boost::asio::io_context io_context_;
        bool isRunning_ { true };
        rtype::Network::UdpServer udp_server_;
        std::unordered_map<BPC::Method, std::shared_ptr<IHandler>> handlers_;

      public:
        std::string id;

        Lobby();
        ~Lobby() = default;

        /**
        * @brief processes the game logic
        */
        void onTick();

        /**
        * @return true the lobby is running
        * @return false the lobby has closed
        */
        bool isRunning() const noexcept;
    };
}
