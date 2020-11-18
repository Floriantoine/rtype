/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** AHandlerUDP
*/

#pragma once

#include "GameClient.hpp"

#include <vector>

namespace rtype::client {
    class AHandlerUDP {
      private:
        std::vector<BPC::Package> awaitingResponse_;

        void refreshServerActiveness_();
        void receiveRequest_(const BPC::Package &package);
        void receiveResponse_(const BPC::Package &package);

      protected:
        GameClient &owner;

        AHandlerUDP(GameClient &client);
        void sendResponse(const BPC::Package &package) const;

        template <typename T>
        void sendResponse(const BPC::Package &package, const T *body) const
        {
            BPC::Package pkg(package, BPC::RESPONSE);

            if (body != nullptr) {
                pkg.setBodyFrom(body);
            } else {
                pkg.body.resize(0);
            }
        }

        virtual BPC::Method getMethod() const = 0;
        virtual void receiveRequest(const BPC::Package &package) = 0;
        virtual void receiveResponse(const BPC::Package &package) = 0;

      public:
        static void unknowPacket(const BPC::Package &package);

        virtual ~AHandlerUDP() = default;
        void receive(const BPC::Package &package);

        template <typename T>
        void sendRequest(const T *body, bool needResponse = true)
        {
            BPC::Package pkg;
            pkg.method = this->getMethod();
            pkg.type = BPC::REQUEST;
            pkg.timestamp = Clock::Now().time_since_epoch().count();
            pkg.setBodyFrom(body);

            if (!this->owner.conn_->send(pkg)) {
                if (needResponse)
                    this->awaitingResponse_.push_back(pkg);
            } else {
                std::cout << "We have to exit here" << std::endl;
            }
        }

        void sendRequest(const BPC::Buffer &buffer, bool needResponse = true);
    };
}
