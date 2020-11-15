/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** AHandler
*/

#include "AHandler.hpp"

namespace rtype::server {
    AHandler::HandlerPtrWrapper::HandlerPtrWrapper(AHandler &handler, method_ptr_t pointer)
        : pointer_(pointer)
        , handler_(handler)
    { }

    void AHandler::HandlerPtrWrapper::operator()(const BPC::Package &package)
    {
        (this->handler_.*pointer_)(package);
    }

    AHandler::HandlerPtrWrapper AHandler::operator[](BPC::BaseType type)
    {
        if (type == BPC::BaseType::REQUEST) {
            return AHandler::HandlerPtrWrapper(*this, &AHandler::request);
        }
        return AHandler::HandlerPtrWrapper(*this, &AHandler::response);
    }
}
