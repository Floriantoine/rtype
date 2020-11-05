/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Server
*/

#include "Server.hpp"

#include "lobby/LobbyDispatcher.hpp"
#include "lobby/LobbyManagerThread.hpp"

#include <chrono>
#include <memory>
#include <thread>

namespace rtype::server {
    Server Server::instance_ = Server();

    void Server::run(const rtype::server::Config &conf)
    {
        Server::instance_.run_(conf);
    }

    void Server::run_(const rtype::server::Config &conf)
    {
        this->dispatcher_ = std::make_shared<LobbyDispatcher>(conf.maxGameThreads);
        for (auto idx = 0u; idx < conf.maxGameThreads; ++idx) {
            this->lobbyManagers_.emplace_back(std::make_unique<LobbyManagerThread>(this->dispatcher_, idx));
        }
    }
}
