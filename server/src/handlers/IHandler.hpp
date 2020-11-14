/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** IHandler
*/

#pragma once

#include "BinaryProtocolCommunication.hpp"

namespace rtype {
    class IHandler {
      private:
        struct HandlerPtrWrapper {
          public:
            typedef void (IHandler::*method_ptr_t)(char *);

          private:
            method_ptr_t pointer_;
            IHandler &handler_;

          public:
            HandlerPtrWrapper(IHandler &handler, method_ptr_t pointer);
            void operator()(char *body);
        };

      protected:
        virtual void request(char *body) = 0;
        virtual void response(char *body) = 0;

      public:
        IHandler() = default;
        virtual ~IHandler() = default;

        HandlerPtrWrapper operator[](BPC::BaseType type);
    };
}
