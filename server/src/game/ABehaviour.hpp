/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Behaviour abstract class
*/

#pragma once

#include "engine/core/ABehaviourBase.hpp"
#include "lobby/Lobby.hpp"

#include <memory>

namespace rtype::server {

    /**
     * Behaviour abstract class
     *
     * Behaviours are entity-specific behaviours
     * Behaviours must inherit from this class to be triggered by the default 
     * systems
     */
    class ABehaviour : public ABehaviourBase {
      protected:
        std::shared_ptr<Lobby> lobby_;

        public:
          void setLobby(const std::shared_ptr<Lobby> &lobby);
    };
}
