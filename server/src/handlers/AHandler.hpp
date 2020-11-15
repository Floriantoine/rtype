/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** AHandler
*/

#pragma once

#include "Protocol.hpp"

#include <unordered_map>
#include <vector>

namespace rtype::server {
    class AHandler {
      private:
        struct HandlerPtrWrapper {
          public:
            typedef void (AHandler::*method_ptr_t)(const BPC::Package &);

          private:
            method_ptr_t pointer_;
            AHandler &handler_;

          public:
            HandlerPtrWrapper(AHandler &handler, method_ptr_t pointer);
            void operator()(const BPC::Package &package);
        };

      protected:
        virtual void request(const BPC::Package &package) = 0;
        virtual void response(const BPC::Package &package) = 0;

        AHandler() = default;

      public:
        virtual ~AHandler() = default;
        HandlerPtrWrapper operator[](BPC::BaseType type);
    };
}
