/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** AHandlerUDP
*/

#include "AHandlerUDP.hpp"

#include "Protocol.hpp"
#include "Server.hpp"
#include "utils/Clock.hpp"

#include <algorithm>

namespace rtype::server {
    AHandlerUDP::HandlerPtrWrapper::HandlerPtrWrapper(AHandlerUDP &handler, HandlerPtrWrapper::method_ptr_t pointer)
        : pointer_(pointer)
        , handler_(handler)
    { }

    void AHandlerUDP::HandlerPtrWrapper::operator()(const Network::UdpPackage &package)
    {
        (this->handler_.*this->pointer_)(package);
    }

    AHandlerUDP::AHandlerUDP(std::vector<Player> &players)
        : players_ { players }
    { }

    AHandlerUDP::HandlerPtrWrapper AHandlerUDP::operator[](BPC::BaseType type)
    {
        if (type == BPC::BaseType::REQUEST) {
            return AHandlerUDP::HandlerPtrWrapper(*this, &AHandlerUDP::request);
        }
        return AHandlerUDP::HandlerPtrWrapper(*this, &AHandlerUDP::response);
    }

    bool AHandlerUDP::resend_(Network::UdpPackage &package)
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