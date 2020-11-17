/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** AHandlerUDP
*/

#include "AHandlerUDP.hpp"

#include "Protocol.hpp"
#include "Server.hpp"
#include "lobby/Lobby.hpp"
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

    AHandlerUDP::AHandlerUDP(Lobby &owner)
        : owner_ { owner }
    { }

    AHandlerUDP::HandlerPtrWrapper AHandlerUDP::operator[](BPC::BaseType type)
    {
        if (type == BPC::BaseType::REQUEST) {
            return AHandlerUDP::HandlerPtrWrapper(*this, &AHandlerUDP::receiveRequest);
        } else if (type == BPC::BaseType::RESPONSE) {
            return AHandlerUDP::HandlerPtrWrapper(*this, &AHandlerUDP::receiveResponse);
        }
        return AHandlerUDP::HandlerPtrWrapper(*this, &AHandlerUDP::other);
    }

    void AHandlerUDP::receiveRequest(const Network::UdpPackage &package)
    {
        this->refreshPlayerActiveness(package);
    }

    void AHandlerUDP::receiveResponse(const Network::UdpPackage &package)
    {
        auto elem = std::find_if(this->awaitingResponse_.begin(), this->awaitingResponse_.end(),
            [&package](const auto &it) {
                return (it.endpoint == package.endpoint && it.timestamp == package.timestamp);
            });
        if (elem != this->awaitingResponse_.end()) {
            this->awaitingResponse_.erase(elem);
        }
        this->refreshPlayerActiveness(package);
    }

    void AHandlerUDP::other(const Network::UdpPackage &package)
    {
        AHandlerUDP::unknowPacket(package);
    }

    bool AHandlerUDP::resend_(Network::UdpPackage &package)
    {
        const auto &player = std::find_if(this->owner_.players_.begin(), this->owner_.players_.end(),
            [&package](const auto &it) {
                return it.endpoint == package.endpoint;
            });
        if (player == this->owner_.players_.end())
            return false;
        package.timestamp = Clock::Now().time_since_epoch().count();
        this->owner_.udpServer_.write(package);
        return true;
    }

    void AHandlerUDP::refreshPlayerActiveness(const Network::UdpPackage &package)
    {
        auto player = std::find_if(this->owner_.players_.begin(), this->owner_.players_.end(),
            [&package](const auto &it) {
                return it.endpoint == package.endpoint;
            });
        if (player != this->owner_.players_.end()) {
            player->activeness.reset();
        }
    }

    void AHandlerUDP::unknowPacket(const Network::UdpPackage &package)
    {
    }

    bool AHandlerUDP::update()
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
        return this->awaitingResponse_.size() != 0;
    }
}
