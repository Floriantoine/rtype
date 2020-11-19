/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Behaviour abstract class
*/

#pragma once

#include "Protocol.hpp"
#include "engine/core/ABehaviourBase.hpp"
#include "engine/core/components/PositionComponent.hpp"
#include "handlers/AHandlerUDP.hpp"
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
        void sendPosition(const PositionComponent *position);

        virtual void onDestroy() override;

        template <typename T>
        void sendRequestToPlayers(BPC::Method method, const T *body, id_t ignore = 0, bool needResponse = true)
        {
            auto &handler = this->lobby_->handlers[method];

            for (const auto &it : this->lobby_->players) {
                if (ignore != 0 && it.id == ignore)
                    continue;
                handler->sendRequest(it.endpoint, body, needResponse);
            }
        }
    };
}
