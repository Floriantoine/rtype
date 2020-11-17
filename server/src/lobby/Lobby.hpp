/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Lobby
*/

#pragma once

#include "Player.hpp"
#include "Server.hpp"
#include "engine/core/scene/SceneManager.hpp"
#include "types.hpp"
#include "utils/Clock.hpp"

#include <bits/types/time_t.h>
#include <chrono>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace rtype::server {
    class AHandlerUDP;
    class ChargeHandler;
    class DestroyHandler;
    class DropHandler;
    class GameStateHandler;
    class GrabHandler;
    class HitHandler;
    class JoinHandler;
    class LeaveHandler;
    class MoveHandler;
    class PositionHandler;
    class ShootHandler;
    class SpawnHandler;

    /**
    * @brief representation of a lobby, where the game logic is processed
    */
    class Lobby {
        friend AHandlerUDP;
        friend ChargeHandler;
        friend DestroyHandler;
        friend DropHandler;
        friend GameStateHandler;
        friend GrabHandler;
        friend HitHandler;
        friend JoinHandler;
        friend LeaveHandler;
        friend MoveHandler;
        friend PositionHandler;
        friend ShootHandler;
        friend SpawnHandler;

      private:
        struct State {
          private:
            GameState state_;
            Clock clock_;

          public:
            GameState operator*() const;
            State &operator=(const GameState newState);
            long elapsed() const;
            void resetClock();
        };

        static constexpr long PLAYER_TIMEOUT_MS = std::chrono::milliseconds(5000).count();
        static constexpr long LOBBY_TIMEOUT_MS = std::chrono::milliseconds(30000).count();
        static constexpr unsigned char MAX_PLAYERS = 4;

        State state_;
        std::vector<Player> players_;
        bool awaitingResponse_ { false };
        std::unique_ptr<SceneManager> sceneManager_;
        Network::UdpServer udpServer_;
        std::unordered_map<BPC::Method, std::shared_ptr<AHandlerUDP>> handlers_;

        void onPacketReceived_(const Network::UdpPackage &package);
        void updateState_();
        void updatePlayersState_();
        void updateGameState_();
        void removePlayer_(const udp::endpoint &endpoint);

      public:
        const std::string id;

        Lobby(const std::string &id, std::unique_ptr<SceneManager> &&sceneManager);
        ~Lobby() = default;

        /**
        * @brief processes the game logic
        */
        void onTick();

        /**
        * @return true the lobby is running
        * @return false the lobby has closed
        */
        bool isRunning() const noexcept;

        /**
        * @brief tells if the lobby has space left for a new player
        */
        bool isFull() const noexcept;

        /**
        * @brief Get the port on which the lobby is running
        */
        unsigned short getPort() const;
    };
}
