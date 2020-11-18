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
    AHandlerUDP::AHandlerUDP(Lobby &owner)
        : owner_ { owner }
    { }

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

    void AHandlerUDP::refreshPlayerActiveness_(const Network::UdpPackage &package)
    {
        auto player = std::find_if(this->owner_.players_.begin(), this->owner_.players_.end(),
            [&package](const auto &it) {
                return it.endpoint == package.endpoint;
            });
        if (player != this->owner_.players_.end()) {
            player->activeness.reset();
        }
    }

    void AHandlerUDP::receiveRequest_(const Network::UdpPackage &package)
    {
        this->refreshPlayerActiveness_(package);
        this->receiveRequest(package);
    }

    void AHandlerUDP::receiveResponse_(const Network::UdpPackage &package)
    {
        auto elem = std::find_if(this->awaitingResponse_.begin(), this->awaitingResponse_.end(),
            [&package](const auto &it) {
                return (it.endpoint == package.endpoint && it.timestamp == package.timestamp);
            });
        if (elem != this->awaitingResponse_.end()) {
            this->awaitingResponse_.erase(elem);
        }
        this->refreshPlayerActiveness_(package);
        this->receiveResponse(package);
    }

    void AHandlerUDP::sendResponse(const Network::UdpPackage &package) const
    {
        this->sendResponse(package, (char *)nullptr);
    }

    void AHandlerUDP::unknowPacket(const Network::UdpPackage &package)
    {
    }

    void AHandlerUDP::receive(const Network::UdpPackage &package)
    {
        if (package.type == BPC::RESPONSE) {
            this->receiveResponse_(package);
        } else if (package.type == BPC::REQUEST) {
            this->receiveRequest_(package);
        } else {
            AHandlerUDP::unknowPacket(package);
        }
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

    template<>
    void AHandlerUDP::sendRequest(const udp::endpoint &endpoint, const BPC::Buffer *buffer, bool needResponse)
    {
        Network::UdpPackage pkg;
        pkg.method = this->getMethod();
        pkg.type = BPC::REQUEST;
        pkg.timestamp = Clock::Now().time_since_epoch().count();
        if (buffer)
            pkg.body = *buffer;
        pkg.endpoint = endpoint;

        if (!this->owner_.udpServer_.write(pkg)) {
            if (needResponse)
                this->awaitingResponse_.push_back(pkg);
        } else {
            this->owner_.removePlayer_(endpoint);
        }
    }
}
