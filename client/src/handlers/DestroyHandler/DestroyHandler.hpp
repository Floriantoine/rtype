/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** DestroyHandler
*/

#pragma once

#include "handlers/AHandlerUDP.hpp"
#include "types.hpp"

#include <vector>

namespace rtype::client {
    class DestroyHandler : public AHandlerUDP {
      public:
        struct ServerRequestBody {
            entity_id_t entityID;
        };

        DestroyHandler(GameClient &owner);
        ~DestroyHandler() override = default;

      protected:
        void receiveResponse(const BPC::Package &package) override;
        void receiveRequest(const BPC::Package &package) override;
        BPC::Method getMethod() const override;
    };
}
