/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** AHandlerTCP
*/

#include "AHandlerTCP.hpp"
#include "GameServer.hpp"

#include <iostream>
#include <string>

namespace rtype::server {
    AHandlerTCP::HandlerPtrWrapper::HandlerPtrWrapper(AHandlerTCP &handler, AHandlerTCP::HandlerPtrWrapper::method_ptr_t pointer)
        : pointer_ { pointer }
        , handler_ { handler }
    {
    }

    void AHandlerTCP::HandlerPtrWrapper::operator()(const BPC::Package &package, Network::TcpSession &client)
    {
        (this->handler_.*this->pointer_)(package, client);
    }

    AHandlerTCP::AHandlerTCP(GameServer &owner)
        : owner_ { owner }
    { }

    void AHandlerTCP::other(const BPC::Package &package, Network::TcpSession &client)
    {
        AHandlerTCP::unknowPacket(package, client);
    }

    void AHandlerTCP::unknowPacket(const BPC::Package &package, Network::TcpSession &client) 
    {
        std::string ip = client.getSocket().local_endpoint().address().to_string();
        auto port = client.getSocket().local_endpoint().port();

        std::cerr << "Received a malformed packed from: " << ip << ":" << port << std::endl;
    }

    AHandlerTCP::HandlerPtrWrapper AHandlerTCP::operator[](BPC::BaseType type)
    {
        if (type == BPC::BaseType::REQUEST) {
            return AHandlerTCP::HandlerPtrWrapper(*this, &AHandlerTCP::receiveRequest);
        } else if (type == BPC::BaseType::RESPONSE) {
            return AHandlerTCP::HandlerPtrWrapper(*this, &AHandlerTCP::receiveResponse);
        }
        return AHandlerTCP::HandlerPtrWrapper(*this, &AHandlerTCP::other);
    }
}