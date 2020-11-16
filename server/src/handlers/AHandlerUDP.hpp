/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** AHandlerUDP
*/

#pragma once

#include "Player.hpp"
#include "Protocol.hpp"
#include "Server.hpp"

#include <chrono>
#include <vector>

namespace rtype::server {
    class AHandlerUDP {
      private:
        static constexpr long RESPONSE_DELAY = std::chrono::milliseconds(400).count();

        std::vector<Player> &players_;
        std::vector<Network::UdpPackage> awaitingResponse_;

        bool resend_(Network::UdpPackage &package);

      protected:
        struct HandlerPtrWrapper {
          public:
            typedef void (AHandlerUDP::*method_ptr_t)(const Network::UdpPackage &);

          private:
            method_ptr_t pointer_;
            AHandlerUDP &handler_;

          public:
            HandlerPtrWrapper(AHandlerUDP &handler, method_ptr_t pointer);
            void operator()(const Network::UdpPackage &package);
        };

        virtual void request(const Network::UdpPackage &package) = 0;
        virtual void response(const Network::UdpPackage &package) = 0;
        void other(const Network::UdpPackage &package);

        AHandlerUDP(std::vector<Player> &players);

      public:
        virtual ~AHandlerUDP() = default;
        virtual HandlerPtrWrapper operator[](BPC::BaseType type);
        void update();
        static void unknowPacket(const Network::UdpPackage &package);
    };
}