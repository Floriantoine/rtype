/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** GameServer
*/

#pragma once

#include "Config.hpp"
#include "Server.hpp"
#include "lobby/Lobby.hpp"
#include "lobby/LobbyDispatcher.hpp"
#include "lobby/LobbyManagerThread.hpp"

#include <memory>
#include <unordered_map>
#include <vector>

namespace rtype::server {

    /**
     * @brief The server's master class (is a singleton)
     */
    class GameServer {
      private:
        static GameServer Instance_;
        std::vector<std::unique_ptr<LobbyManagerThread>> lobbyManagers_;
        std::shared_ptr<LobbyDispatcher> dispatcher_;
        boost::asio::io_context io_context_;
        std::unordered_map<BPC::Method, std::shared_ptr<AHandler>> handlers_;
        Network::TcpServer master_;

        GameServer(const Config &conf);
        void run_(const Config &conf);

      public:
        ~GameServer() = default;
        /**
        * @brief start running the server: accepting connections and running games
        * 
        * @param conf server's configuration
        */
        static void Run(const Config &conf);
    };
}
