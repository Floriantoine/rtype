/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** GameServer
*/

#include "GameServer.hpp"

#include "Protocol.hpp"
#include "lobby/LobbyDispatcher.hpp"
#include "lobby/LobbyManagerThread.hpp"
#include "scene_loader/SceneLoader.hpp"

#include <algorithm>
#include <chrono>
#include <memory>
#include <thread>

namespace rtype::server {
    GameServer::GameServer(const server::Config &conf)
        : config_(conf)
        , dispatcher_ { std::make_shared<LobbyDispatcher>(conf.maxGameThreads) }
        , handlers_ {
            { BPC::ASK_JOIN, std::make_shared<AskJoinHandler>(*this) },
            { BPC::CREATE, std::make_shared<CreateHandler>(*this) }
        }
        , master_(io_context_, conf.port, [&](const BPC::Package &package, Network::TcpSession &client) {
            this->onPacketReceived_(package, client);
        })
    {
        JsonLoader::loadDefinitions(this->config_.definitionsPath);
        for (auto idx = 0u; idx < conf.maxGameThreads; ++idx) {
            this->lobbyManagers_.emplace_back(std::make_unique<LobbyManagerThread>(this->dispatcher_));
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

    void GameServer::onPacketReceived_(const BPC::Package &package, Network::TcpSession &client)
    {
        auto it = std::find_if(
            this->handlers_.cbegin(),
            this->handlers_.cend(),
            [&package](const auto &it) {
                return package.method == it.first;
            });

        if (it != this->handlers_.cend()) {
            (*it->second)[package.type](package, client);
        } else {
            AHandlerTCP::unknowPacket(package, client);
        }
    }
}
