/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** JoinHandler
*/

#pragma once

#include "engine/core/ecs/entity/Entity.hpp"
#include "handlers/AHandlerUDP.hpp"
#include "types.hpp"

#include <memory>
#include <vector>

namespace rtype::client {
    class JoinHandler : public AHandlerUDP {
      public:
        struct ServerResponseBody {
            entity_id_t playerID;
            coordinate_t x;
            coordinate_t y;
            std::vector<unsigned char> mapName;
        };

        JoinHandler(GameClient &owner);
        ~JoinHandler() override = default;

      protected:
        void receiveResponse(const BPC::Package &package) override;
        void receiveRequest(const BPC::Package &package) override;
        BPC::Method getMethod() const override;
        void refusePlayer(const BPC::Package &package) const;
        void newPlayer(const BPC::Package &package, const std::shared_ptr<Entity> &player) const;
    };
}
