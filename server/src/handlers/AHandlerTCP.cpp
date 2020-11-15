/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** AHandlerTCP
*/

#include "AHandlerTCP.hpp"

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

    AHandlerTCP::AHandlerTCP(LobbyDispatcher &dispatcher)
        : dispatcher_ { dispatcher }
    { }

    AHandlerTCP::HandlerPtrWrapper AHandlerTCP::operator[](BPC::BaseType type)
    {
        if (type == BPC::BaseType::REQUEST) {
            return AHandlerTCP::HandlerPtrWrapper(*this, &AHandlerTCP::request);
        }
        return AHandlerTCP::HandlerPtrWrapper(*this, &AHandlerTCP::response);
    }
}