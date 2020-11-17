/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** AHandlerUDP
*/

#pragma once

#include "Player.hpp"
#include "Protocol.hpp"
#include "Server.hpp"
#include "lobby/Lobby.hpp"

#include <chrono>
#include <vector>

namespace rtype::server {
    class AHandlerUDP {
      private:
        static constexpr long RESPONSE_DELAY = std::chrono::milliseconds(400).count();

        std::vector<Network::UdpPackage> awaitingResponse_;

        bool resend_(Network::UdpPackage &package);
        void refreshPlayerActiveness_(const Network::UdpPackage &package);
        void receiveRequest_(const Network::UdpPackage &package);
        void receiveResponse_(const Network::UdpPackage &package);

      protected:
        Lobby &owner_;

        AHandlerUDP(Lobby &owner);
        virtual BPC::Method getMethod() const = 0;
        virtual void receiveRequest(const Network::UdpPackage &package) = 0;
        virtual void receiveResponse(const Network::UdpPackage &package) = 0;
        void other(const Network::UdpPackage &package);

        template <typename T>
        void sendResponse(const Network::UdpPackage &package, const T &body, bool needResponse = true)
        {
            Network::UdpPackage pkg = package;
            pkg.type = BPC::RESPONSE;
            pkg.setBodyFrom(&body);

            if (!this->owner_.udpServer_.write(package)) {
                if (needResponse)
                    this->awaitingResponse_.push_back(package);
            } else {
                this->owner_.removePlayer_(pkg.endpoint);
            }
        }

      public:
        static void unknowPacket(const Network::UdpPackage &package);

        virtual ~AHandlerUDP() = default;
        void receive(const Network::UdpPackage &package);
        bool update();

        template <typename T>
        void sendRequest(const udp::endpoint &endpoint, const T &body, bool needResponse = true)
        {
            Network::UdpPackage pkg;
            pkg.method = this->getMethod();
            pkg.type = BPC::REQUEST;
            pkg.timestamp = Clock::Now().time_since_epoch().count();
            pkg.setBodyFrom(&body);
            pkg.endpoint = endpoint;

            if (!this->owner_.udpServer_.write(pkg)) {
                if (needResponse)
                    this->awaitingResponse_.push_back(pkg);
            } else {
                this->owner_.removePlayer_(endpoint);
            }
        }
    };
}
