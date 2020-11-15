/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** GameServer
*/

#include "GameServer.hpp"

#include "Protocol.hpp"
#include "handlers/TCP/AskJoinHandler/AskJoinHandler.hpp"
#include "handlers/TCP/CreateHandler/CreateHandler.hpp"
#include "lobby/LobbyDispatcher.hpp"
#include "lobby/LobbyManagerThread.hpp"

#include <chrono>
#include <memory>
#include <thread>

namespace rtype::server {
    GameServer::GameServer(const server::Config &conf)
        : handlers_ {
            { BPC::ASK_JOIN, std::make_shared<AskJoinHandler>() },
            { BPC::CREATE, std::make_shared<CreateHandler>() }
        }
        , master_(io_context_, conf.port, [&](const BPC::Package &package) {
            (*this->handlers_[package.method])[package.type](package);
        })
    { }

    void GameServer::Run(const Config &conf)
    {
        static GameServer instance(conf);

        instance.run_(conf);
    }

    void GameServer::run_(const Config &conf)
    {
        this->dispatcher_ = std::make_shared<LobbyDispatcher>(conf.maxGameThreads);
        for (auto idx = 0u; idx < conf.maxGameThreads; ++idx) {
            this->lobbyManagers_.emplace_back(std::make_unique<LobbyManagerThread>(this->dispatcher_, idx));
        }
        this->io_context_.run();
    }
}
