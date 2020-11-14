/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Lobby
*/

#include "Lobby.hpp"

#include "Server.hpp"

namespace rtype::server {
    Lobby::Lobby()
        : udp_server_(io_context_)
    {
    }

    void Lobby::onTick()
    {
        std::cout << "Here" << std::endl;
        this->udp_server_.io_context_.run();
    }

    bool Lobby::isRunning() const noexcept
    {
        return this->isRunning_;
    }
}
