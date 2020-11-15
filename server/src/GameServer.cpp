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
        : dispatcher_ { std::make_shared<LobbyDispatcher>(conf.maxGameThreads) }
        , handlers_ {
            { BPC::ASK_JOIN, std::make_shared<AskJoinHandler>(*this->dispatcher_) },
            { BPC::CREATE, std::make_shared<CreateHandler>(*this->dispatcher_) }
        }
        , master_(io_context_, conf.port, [&](const BPC::Package &package, Network::TcpSession &client) {
            (*this->handlers_[package.method])[package.type](package, client);
        })
    {
        for (auto idx = 0u; idx < conf.maxGameThreads; ++idx) {
            this->lobbyManagers_.emplace_back(std::make_unique<LobbyManagerThread>(this->dispatcher_, idx));
        }
    }

    void GameServer::Run(const Config &conf)
    {
        static GameServer instance(conf);

        instance.run_();
    }

    void GameServer::run_()
    {
        this->io_context_.run();
    }
}
