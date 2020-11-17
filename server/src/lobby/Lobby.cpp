/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Lobby
*/

#include "Lobby.hpp"

#include "Protocol.hpp"
#include "Server.hpp"
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
        return this->state_;
    }

    Lobby::State &Lobby::State::operator=(const GameState newState)
    {
        this->state_ = newState;
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

    Lobby::Lobby(const std::string &id, std::unique_ptr<SceneManager> &&sceneManager)
        : sceneManager_ { std::move(sceneManager) }
        , udpServer_([&](const Network::UdpPackage &package) {
            this->onPacketReceived_(package);
        })
        , handlers_ {
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
    {
        this->state_ = GameState::AWT_START;
        this->udpServer_.start();
    }

    void Lobby::onTick()
    {
        this->udpServer_.poll();
        this->awaitingResponse_ = false;
        for (const auto &it : this->handlers_) {
            this->awaitingResponse_ = it.second->update() || this->awaitingResponse_;
        }
        if (*this->state_ == GameState::RUN) {
            auto elapsed = this->state_.elapsed();
            this->state_.resetClock();
            this->sceneManager_->update(elapsed);
        }
        this->updateState_();
    }

    bool Lobby::isRunning() const noexcept
    {
        return (*this->state_ != GameState::AWT_START
            && *this->state_ != GameState::RUN
            && !this->awaitingResponse_
        );
    }

    bool Lobby::isFull() const noexcept
    {
        return this->players_.size() >= MAX_PLAYERS;
    }

    unsigned short Lobby::getPort() const
    {
        return this->udpServer_.getPort();
    }

    void Lobby::onPacketReceived_(const Network::UdpPackage &package)
    {
        auto it = std::find_if(
            this->handlers_.cbegin(),
            this->handlers_.cend(),
            [&package](const auto &it) {
                return package.method == it.first;
            });

        if (it != this->handlers_.cend()) {
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
        auto player = this->players_.begin();
        DestroyHandler::ServerRequestBody body;
        auto &handler = this->handlers_[BPC::LEAVE];

        for (; player != this->players_.end(); ++player) {
            if (player->activeness.getElapsedMillisecond() < PLAYER_TIMEOUT_MS)
                continue;
            body.entityID = player->id;
            player = this->players_.erase(player);
            for (const auto &it : this->players_) {
                handler->sendRequest(it.endpoint, body);
            }
        }
    }

    void Lobby::updateGameState_()
    {
        GameStateHandler::ServerRequestBody body;

        if (*this->state_ != GameState::RUN) {
            if (this->state_.elapsed() >= LOBBY_TIMEOUT_MS) {
                this->state_ = GameState::TIMEOUT;
                body.state = GameState::TIMEOUT;
                auto handler = this->handlers_[BPC::GAME_STATE];
                for (const auto &it : this->players_) {
                    handler->sendRequest(it.endpoint, body);
                }
            }
        } else if (*this->state_ != GameState::AWT_START && this->players_.size() == 0) {
            this->state_ = GameState::TIMEOUT;
        }
    }

    void Lobby::removePlayer_(const udp::endpoint &endpoint)
    {
        auto it = std::find_if(this->players_.begin(), this->players_.end(),
            [&endpoint](const auto &it) {
                return it.endpoint == endpoint;
            });
        if (it != this->players_.end()) {
            this->players_.erase(it);
        }
    }
}
