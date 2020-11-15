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
            { BPC::GAME_STATE, std::make_shared<GameStateHandler>() },
            { BPC::MOVE, std::make_shared<MoveHandler>() },
            { BPC::SPAWN, std::make_shared<SpawnHandler>() },
            { BPC::DESTROY, std::make_shared<DestroyHandler>() },
            { BPC::GRAB, std::make_shared<GrabHandler>() },
            { BPC::DROP, std::make_shared<DropHandler>() },
            { BPC::CHARGE, std::make_shared<ChargeHandler>() },
            { BPC::SHOOT, std::make_shared<ShootHandler>() },
            { BPC::HIT, std::make_shared<HitHandler>() },
            { BPC::JOIN, std::make_shared<JoinHandler>() },
            { BPC::LEAVE, std::make_shared<LeaveHandler>() }
        }
    {
    }

    void Lobby::onTick()
    {
        this->udp_server_.read([&](const BPC::Package &package) {
            (*this->handlers_[package.method])[package.type](package);
        });
        // this->scene_->update();
        this->io_context_.run();
    }

    bool Lobby::isRunning() const noexcept
    {
        return this->isRunning_;
    }
}
