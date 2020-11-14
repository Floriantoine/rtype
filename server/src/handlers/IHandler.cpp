/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** IHandler
*/

#include "IHandler.hpp"

namespace rtype {
    IHandler::HandlerPtrWrapper::HandlerPtrWrapper(IHandler &handler, method_ptr_t pointer)
        : pointer_(pointer)
        , handler_(handler)
    { }

    void IHandler::HandlerPtrWrapper::operator()(char *body)
    {
        (this->handler_.*pointer_)(body);
    }

    IHandler::HandlerPtrWrapper IHandler::operator[](BPC::BaseType type)
    {
        if (type == BPC::BaseType::REQUEST) {
            return IHandler::HandlerPtrWrapper(*this, &IHandler::request);
        }
        return IHandler::HandlerPtrWrapper(*this, &IHandler::response);
    }
}
