/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Lobby
*/

#pragma once

#include "Player.hpp"
#include "Server.hpp"
#include "engine/core/ecs/entity/Entity.hpp"
#include "engine/core/ecs/types.hpp"
#include "engine/core/scene/Scene.hpp"
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

    /**
    * @brief representation of a lobby, where the game logic is processed
    */
    class Lobby : public std::enable_shared_from_this<Lobby> {
        friend AHandlerUDP;

      private:
        struct State {
          private:
            GameState state;
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

        bool awaitingResponse_ { false };
        Network::UdpServer udpServer_;

        void onPacketReceived_(const Network::UdpPackage &package) const;
        void updateState_();
        void updatePlayersState_();
        void updateGameState_();

      public:
        const std::string id;
        const std::string map;

        State state;
        std::vector<Player> players;
        std::shared_ptr<Scene> scene;
        std::unordered_map<BPC::Method, std::shared_ptr<AHandlerUDP>> handlers;

        Lobby(const std::string &id, std::shared_ptr<Scene> &&scene, const std::string &mapName);
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

        void removePlayer(const udp::endpoint &endpoint);
        std::shared_ptr<Entity> getEntity(id_t id);

        template <typename T>
        T *getEntityComponent(id_t id)
        {
            auto entity = this->getEntity(id);
            if (!entity)
                return nullptr;
            return entity->getComponent<T>();
        }
    };
}
