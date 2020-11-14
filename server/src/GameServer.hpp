/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** GameServer
*/

#pragma once

#include "Config.hpp"
#include "lobby/Lobby.hpp"
#include "lobby/LobbyDispatcher.hpp"
#include "lobby/LobbyManagerThread.hpp"

#include <boost/asio.hpp>
#include <memory>
#include <vector>

namespace rtype::server {

    /**
     * @brief The server's master class (is a singleton)
     */
    class GameServer {
      private:
        std::shared_ptr<boost::asio::io_context> io_context_;
        static GameServer Instance_;
        std::vector<std::unique_ptr<LobbyManagerThread>> lobbyManagers_;
        std::shared_ptr<LobbyDispatcher> dispatcher_;

        GameServer() = default;
        void run_(const rtype::server::Config &conf);

      public:
        ~GameServer() = default;
        /**
        * @brief start running the server: accepting connections and running games
        * 
        * @param conf server's configuration
        */
        static void Run(const rtype::server::Config &conf);
    };
}
