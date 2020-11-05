/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Server
*/

#pragma once

#include "Config.hpp"
#include "lobby/Lobby.hpp"
#include "lobby/LobbyDispatcher.hpp"
#include "lobby/LobbyManagerThread.hpp"

#include <memory>
#include <vector>

namespace RType {

    /**
     * @brief The server's main class (is a singleton)
     */
    class Server {
      private:
        static Server instance_;
        std::vector<std::unique_ptr<LobbyManagerThread>> lobbyManagers_;
        std::shared_ptr<LobbyDispatcher> dispatcher_;

        Server() = default;
        void run_(const RType::Config &conf);

      public:
        ~Server() = default;
        static void run(const RType::Config &conf);
    };
}