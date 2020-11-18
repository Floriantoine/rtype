/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** AHandlerUDP
*/

#include "AHandlerUDP.hpp"

#include "utils/Clock.hpp"

#include <algorithm>

namespace rtype::client {
    AHandlerUDP::AHandlerUDP(GameClient &owner)
        : owner { owner }
    { }

    void AHandlerUDP::refreshServerActiveness_()
    {
        this->owner.activeness.reset();
    }

    void AHandlerUDP::receiveRequest_(const BPC::Package &package)
    {
        this->refreshServerActiveness_();
        this->receiveRequest(package);
    }

    void AHandlerUDP::receiveResponse_(const BPC::Package &package)
    {
        auto elem = std::find_if(this->awaitingResponse_.begin(), this->awaitingResponse_.end(),
            [&package](const auto &it) {
                return (it.timestamp == package.timestamp);
            });
        if (elem != this->awaitingResponse_.end()) {
            this->awaitingResponse_.erase(elem);
        }
        this->refreshServerActiveness_();
        this->receiveResponse(package);
    }

    void AHandlerUDP::sendResponse(const BPC::Package &package) const
    {
        this->sendResponse(package, (char *)nullptr);
    }

    void AHandlerUDP::unknowPacket(const BPC::Package &package)
    {
    }

    void AHandlerUDP::receive(const BPC::Package &package)
    {
        if (package.type == BPC::RESPONSE) {
            this->receiveResponse_(package);
        } else if (package.type == BPC::REQUEST) {
            this->receiveRequest_(package);
        } else {
            AHandlerUDP::unknowPacket(package);
        }
    }

    void AHandlerUDP::sendRequest(const BPC::Buffer &buffer, bool needResponse)
    {
        BPC::Package pkg;
        pkg.method = this->getMethod();
        pkg.type = BPC::REQUEST;
        pkg.timestamp = Clock::Now().time_since_epoch().count();
        pkg.body = buffer;

        if (!this->owner.conn_->send(pkg)) {
            if (needResponse)
                this->awaitingResponse_.push_back(pkg);
        } else {
            std::cout << "We have to exit here" << std::endl;
        }
    }
}
