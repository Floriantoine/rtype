/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** AHandlerTCP
*/

#pragma once

#include "Server.hpp"
#include "lobby/LobbyDispatcher.hpp"

namespace rtype::server {

    class AHandlerTCP {
      private:
        struct HandlerPtrWrapper {
          public:
            typedef void (AHandlerTCP::*method_ptr_t)(const BPC::Package &, Network::TcpSession &);

          private:
            method_ptr_t pointer_;
            AHandlerTCP &handler_;

          public:
            HandlerPtrWrapper(AHandlerTCP &handler, method_ptr_t pointer);
            void operator()(const BPC::Package &package, Network::TcpSession &client);
        };

      protected:
        LobbyDispatcher &dispatcher_;

        AHandlerTCP(LobbyDispatcher &dispatcher);

        virtual void request(const BPC::Package &package, Network::TcpSession &client) = 0;
        virtual void response(const BPC::Package &package, Network::TcpSession &client) = 0;
        void other(const BPC::Package &package, Network::TcpSession &client);

      public:
        virtual ~AHandlerTCP() = default;
        HandlerPtrWrapper operator[](BPC::BaseType type);
        static void unknowPacket(const BPC::Package &package, Network::TcpSession &client);
    };
}
