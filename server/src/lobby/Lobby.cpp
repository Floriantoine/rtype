/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Lobby
*/

#include "Lobby.hpp"

namespace rtype::server {
    void Lobby::onTick()
    {
    }

    bool Lobby::isRunning() const noexcept
    {
        return this->isRunning_;
    }
}