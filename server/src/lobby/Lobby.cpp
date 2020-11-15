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
#include "handlers/UDP/ShootHandler/ShootHandler.hpp"
#include "handlers/UDP/SpawnHandler/SpawnHandler.hpp"

#include <iostream>
#include <memory>

namespace rtype::server {
    Lobby::Lobby()
        : udp_server_(io_context_)
        , handlers_ {
            { BPC::GAME_STATE, std::make_shared<GameStateHandler>(this->players_) },
            { BPC::MOVE, std::make_shared<MoveHandler>(this->players_) },
            { BPC::SPAWN, std::make_shared<SpawnHandler>(this->players_) },
            { BPC::DESTROY, std::make_shared<DestroyHandler>(this->players_) },
            { BPC::GRAB, std::make_shared<GrabHandler>(this->players_) },
            { BPC::DROP, std::make_shared<DropHandler>(this->players_) },
            { BPC::CHARGE, std::make_shared<ChargeHandler>(this->players_) },
            { BPC::SHOOT, std::make_shared<ShootHandler>(this->players_) },
            { BPC::HIT, std::make_shared<HitHandler>(this->players_) },
            { BPC::JOIN, std::make_shared<JoinHandler>(this->players_) },
            { BPC::LEAVE, std::make_shared<LeaveHandler>(this->players_) }
        }
    {
        this->udp_server_.read([&](const BPC::Package &package) {
            (*this->handlers_[package.method])[package.type](package);
        });
    }

    void Lobby::onTick()
    {
        this->io_context_.poll();
        for (const auto &it : this->handlers_) {
            it.second->update();
        }
        // TODO timeout players && timeout lobby
        // this->scene_->update();
    }

    bool Lobby::isRunning() const noexcept
    {
        return this->isRunning_;
    }
}
