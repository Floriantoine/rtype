/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Lobby
*/

#pragma once

#include "Server.hpp"
#include "handlers/AHandlerUDP.hpp"

#include <chrono>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace rtype::server {
    /**
    * @brief representation of a lobby, where the game logic is processed
    */
    class Lobby {
      private:
        static constexpr long PLAYER_TIMEOUT = std::chrono::seconds(5).count();
        static constexpr long LOBBY_TIMEOUT = std::chrono::seconds(30).count();
        static constexpr unsigned char MAX_PLAYERS = 4;

        boost::asio::io_context io_context_;
        bool isRunning_ { true };
        Network::UdpServer udp_server_;
        std::vector<Player> players_;
        std::unordered_map<BPC::Method, std::shared_ptr<AHandlerUDP>> handlers_;

      public:
        const std::string id;

        Lobby(const std::string &id);
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

        /**
        * @brief tells if the lobby has space left for a new player
        */
        bool isFull() const noexcept;

        /**
        * @brief Get the port on which the lobby is running
        */
        unsigned short getPort() const;
    };
}
