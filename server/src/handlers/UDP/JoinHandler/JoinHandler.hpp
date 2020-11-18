/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** JoinHandler
*/

#pragma once

#include "Player.hpp"
#include "engine/core/ecs/entity/Entity.hpp"
#include "handlers/AHandlerUDP.hpp"
#include "types.hpp"

#include <memory>
#include <vector>

namespace rtype::server {
    class JoinHandler : public AHandlerUDP {
      public:
        struct ServerResponseBody {
            entity_id_t playerID;
            coordinate_t x;
            coordinate_t y;
            std::vector<unsigned char> mapName;
        };

        JoinHandler(Lobby &owner);
        ~JoinHandler() override = default;

      protected:
        void receiveResponse(const Network::UdpPackage &package) override;
        void receiveRequest(const Network::UdpPackage &package) override;
        BPC::Method getMethod() const override;
        void refusePlayer(const Network::UdpPackage &package) const;
        void newPlayer(const Network::UdpPackage &package, const std::shared_ptr<Entity> &player) const;
    };
}
