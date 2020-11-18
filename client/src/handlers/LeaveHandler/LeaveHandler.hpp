/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** LeaveHandler
*/

#pragma once

#include "handlers/AHandlerUDP.hpp"
#include "types.hpp"

#include <vector>

namespace rtype::client {
    class LeaveHandler : public AHandlerUDP {
      public:
        struct ClientRequestBody {
            entity_id_t playerID;
        };

        LeaveHandler(GameClient &owner);
        ~LeaveHandler() override = default;

      protected:
        void receiveResponse(const BPC::Package &package) override;
        void receiveRequest(const BPC::Package &package) override;
        BPC::Method getMethod() const override;
    };
}
