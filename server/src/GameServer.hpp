/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** GameServer
*/

#pragma once

#include "Config.hpp"
#include "Server.hpp"
#include "handlers/TCP/AskJoinHandler/AskJoinHandler.hpp"
#include "handlers/TCP/CreateHandler/CreateHandler.hpp"
#include "lobby/Lobby.hpp"
#include "lobby/LobbyDispatcher.hpp"
#include "lobby/LobbyManagerThread.hpp"
#include "handlers/AHandlerTCP.hpp"

#include <memory>
#include <unordered_map>
#include <vector>

namespace rtype::server {

    /**
     * @brief The server's master class (is a singleton)
     */
    class GameServer {
        friend CreateHandler;
        friend AskJoinHandler;

      private:
        boost::asio::io_context io_context_;
        std::vector<std::unique_ptr<LobbyManagerThread>> lobbyManagers_;
        const Config &config_;
        std::shared_ptr<LobbyDispatcher> dispatcher_;
        std::unordered_map<BPC::Method, std::shared_ptr<AHandlerTCP>> handlers_;
        Network::TcpServer master_;

        GameServer(const Config &conf);
        void run_();
        void onPacketReceived_(const BPC::Package &package, Network::TcpSession &client);

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
