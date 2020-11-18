/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Behaviour abstract class
*/

#include "ABehaviour.hpp"

namespace rtype::server {
    void ABehaviour::setLobby(const std::shared_ptr<Lobby> &lobby)
    {
        this->lobby_ = lobby;
    }
}
