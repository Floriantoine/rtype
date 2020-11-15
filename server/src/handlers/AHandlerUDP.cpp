/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** AHandlerUDP
*/

#include "AHandlerUDP.hpp"

#include "Protocol.hpp"
#include "utils/Clock.hpp"

#include <algorithm>

namespace rtype::server {
    AHandlerUDP::AHandlerUDP(std::vector<Player> &players)
        : players_ { players }

    { }

    bool AHandlerUDP::resend_(BPC::Package &package)
    {
        const auto &player = std::find_if(this->players_.begin(), this->players_.end(),
            [&package](const auto &it) {
                return it.endpoint == package.endpoint;
            });
        if (player == this->players_.end())
            return false;
        package.timestamp = Clock::Now().time_since_epoch().count();
        // TODO send message again
        return true;
    }

    void AHandlerUDP::update()
    {
        long now = Clock::Now().time_since_epoch().count();
        auto it = this->awaitingResponse_.begin();

        for (; it != this->awaitingResponse_.end(); ++it) {
            if (now - it->timestamp < RESPONSE_DELAY)
                continue;
            if (!this->resend_(*it)) {
                it = this->awaitingResponse_.erase(it);
            }
        }
    }
}