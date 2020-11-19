/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Lobby
*/

#include "Lobby.hpp"

#include "Protocol.hpp"
#include "Server.hpp"
#include "engine/core/components/HealthComponent.hpp"
#include "engine/core/scene/Scene.hpp"
#include "handlers/TCP/AskJoinHandler/AskJoinHandler.hpp"
#include "handlers/TCP/CreateHandler/CreateHandler.hpp"
#include "handlers/UDP/ChargeHandler/ChargeHandler.hpp"
#include "handlers/UDP/DestroyHandler/DestroyHandler.hpp"
#include "handlers/UDP/DropHandler/DropHandler.hpp"
#include "handlers/UDP/GameStateHandler/GameStateHandler.hpp"
#include "handlers/UDP/GrabHandler/GrabHandler.hpp"
#include "handlers/UDP/HitHandler/HitHandler.hpp"
#include "handlers/UDP/JoinHandler/JoinHandler.hpp"
#include "handlers/UDP/LeaveHandler/LeaveHandler.hpp"
#include "handlers/UDP/MoveHandler/MoveHandler.hpp"
#include "handlers/UDP/PositionHandler/PositionHandler.hpp"
#include "handlers/UDP/ShootHandler/ShootHandler.hpp"
#include "handlers/UDP/SpawnHandler/SpawnHandler.hpp"
#include "types.hpp"
#include "utils/Clock.hpp"

#include <algorithm>
#include <iostream>
#include <memory>
#include <pstl/glue_algorithm_defs.h>
#include <string>

namespace rtype::server {
    GameState Lobby::State::operator*() const
    {
        return this->state;
    }

    Lobby::State &Lobby::State::operator=(const GameState newState)
    {
        this->state = newState;
        this->resetClock();
        return *this;
    }

    long Lobby::State::elapsed() const
    {
        return this->clock_.getElapsedMillisecond();
    }

    void Lobby::State::resetClock()
    {
        this->clock_.reset();
    }

    Lobby::Lobby(const std::string &id, std::shared_ptr<Scene> &&scene, const std::string &mapName)
        : scene { std::move(scene) }
        , udpServer_([&](const Network::UdpPackage &package) {
            this->onPacketReceived_(package);
        })
        , handlers {
            { BPC::GAME_STATE, std::make_shared<GameStateHandler>(*this) },
            { BPC::MOVE, std::make_shared<MoveHandler>(*this) },
            { BPC::SPAWN, std::make_shared<SpawnHandler>(*this) },
            { BPC::DESTROY, std::make_shared<DestroyHandler>(*this) },
            { BPC::GRAB, std::make_shared<GrabHandler>(*this) },
            { BPC::DROP, std::make_shared<DropHandler>(*this) },
            { BPC::CHARGE, std::make_shared<ChargeHandler>(*this) },
            { BPC::SHOOT, std::make_shared<PositionHandler>(*this) },
            { BPC::SHOOT, std::make_shared<ShootHandler>(*this) },
            { BPC::HIT, std::make_shared<HitHandler>(*this) },
            { BPC::JOIN, std::make_shared<JoinHandler>(*this) },
            { BPC::LEAVE, std::make_shared<LeaveHandler>(*this) }
        }
        , id { id }
        , map { mapName }
    {
        this->state = GameState::AWT_START;
        this->udpServer_.start();
    }

    void Lobby::onTick()
    {
        this->udpServer_.poll();
        this->awaitingResponse_ = false;
        for (const auto &it : this->handlers) {
            this->awaitingResponse_ = it.second->update() || this->awaitingResponse_;
        }
        if (*this->state == GameState::RUN) {
            auto elapsed = this->state.elapsed();
            this->state.resetClock();
            this->scene->update(elapsed);
        }
        this->updateState_();
    }

    bool Lobby::isRunning() const noexcept
    {
        return (*this->state != GameState::AWT_START
            && *this->state != GameState::RUN
            && !this->awaitingResponse_);
    }

    bool Lobby::isFull() const noexcept
    {
        return this->players.size() >= MAX_PLAYERS;
    }

    unsigned short Lobby::getPort() const
    {
        return this->udpServer_.getPort();
    }

    void Lobby::onPacketReceived_(const Network::UdpPackage &package) const
    {
        auto it = std::find_if(
            this->handlers.cbegin(),
            this->handlers.cend(),
            [&package](const auto &it) {
                return package.method == it.first;
            });

        if (it != this->handlers.cend()) {
            it->second->receive(package);
        } else {
            AHandlerUDP::unknowPacket(package);
        }
    }

    void Lobby::updateState_()
    {
        this->updatePlayersState_();
        this->updateGameState_();
    }

    void Lobby::updatePlayersState_()
    {
        auto player = this->players.begin();
        DestroyHandler::ServerRequestBody body {};
        auto &handler = this->handlers[BPC::LEAVE];

        for (; player != this->players.end(); ++player) {
            if (player->activeness.getElapsedMillisecond() < PLAYER_TIMEOUT_MS) {
                continue;
            }
            body.entityID = player->id;
            player = this->players.erase(player);
            for (const auto &it : this->players) {
                handler->sendRequest(it.endpoint, &body);
            }
        }
    }

    void Lobby::updateGameState_()
    {
        GameStateHandler::ServerRequestBody body {};

        if (*this->state != GameState::RUN) {
            if (this->state.elapsed() >= LOBBY_TIMEOUT_MS) {
                this->state = GameState::TIMEOUT;
                body.state = GameState::TIMEOUT;
                auto handler = this->handlers[BPC::GAME_STATE];
                for (const auto &it : this->players) {
                    handler->sendRequest(it.endpoint, &body);
                }
            }
        } else if (*this->state != GameState::AWT_START && this->players.empty()) {
            this->state = GameState::TIMEOUT;
        }
    }

    void Lobby::removePlayer(const udp::endpoint &endpoint)
    {
        auto it = std::find_if(this->players.begin(), this->players.end(),
            [&endpoint](const auto &it) {
                return it.endpoint == endpoint;
            });
        auto *health = this->getEntityComponent<HealthComponent>(it->id);
        health->health = 0;
        if (it != this->players.end()) {
            this->players.erase(it);
        }
    }

    std::shared_ptr<Entity> Lobby::getEntity(id_t id)
    {
        return this->scene->getEntityManager().getEntity(id);
    }
}
