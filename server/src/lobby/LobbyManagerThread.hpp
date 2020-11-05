/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** LobbyManagerThread
*/

#pragma once

#include "Lobby.hpp"
#include "LobbyDispatcher.hpp"

#include <list>
#include <memory>
#include <thread>

namespace RType {

    /**
    * @brief a threaded lobby manager to process a list of lobbies
    */
    class LobbyManagerThread {
      private:
        static constexpr unsigned TICKS_PER_SEC = 60;
        static constexpr auto TICK_TIME = std::chrono::seconds(1) / TICKS_PER_SEC;
        bool isRunning_ { false };
        std::shared_ptr<LobbyDispatcher> dispatcher_;
        unsigned index_;
        std::thread thread_;

        void onTick_();

      public:
        LobbyManagerThread(std::shared_ptr<LobbyDispatcher> dispatcher, unsigned index);
        ~LobbyManagerThread();
        void run();
    };
}
