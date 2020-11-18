/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** SpawnHandler
*/

#pragma once

#include "Player.hpp"
#include "handlers/AHandlerUDP.hpp"
#include "types.hpp"

#include <string>
#include <vector>

namespace rtype::server {
    class SpawnHandler : public AHandlerUDP {
      public:
        struct ServerRequestBody {
            entity_id_t entityID;
            std::string jsonBody;
        };

        SpawnHandler(Lobby &owner);
        ~SpawnHandler() override = default;

      protected:
        void receiveResponse(const Network::UdpPackage &package) override;
        void receiveRequest(const Network::UdpPackage &package) override;
        BPC::Method getMethod() const override;
    };
}
