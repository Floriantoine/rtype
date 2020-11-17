/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** ChargeHandler
*/

#include "ChargeHandler.hpp"
#include "Protocol.hpp"
#include "lobby/Lobby.hpp"

namespace rtype::server {
    ChargeHandler::ChargeHandler(Lobby &owner)
        : AHandlerUDP(owner)
    {
    }

    void ChargeHandler::receiveRequest(const Network::UdpPackage &package)
    {
    }

    void ChargeHandler::receiveResponse(const Network::UdpPackage &package)
    {
    }
    
    BPC::Method ChargeHandler::getMethod() const
    {
        return BPC::CHARGE;
    }
}
