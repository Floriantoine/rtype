/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** LobbyDispatcher
*/

#pragma once

#include "Lobby.hpp"
#include "boost/thread/pthread/condition_variable.hpp"
#include "engine/core/scene/Scene.hpp"
#include "engine/core/scene/SceneManager.hpp"
#include "lobby/LobbyIDGenerator.hpp"
#include "utils/lock/SharedLock.hpp"

#include <list>
#include <memory>
#include <queue>
#include <shared_mutex>
#include <string>
#include <vector>

namespace rtype::server {

    /**
    * @brief LobbyManagerThread instances get their lobbies from this class, which holds all lobbies
    */
    class LobbyDispatcher {
      public:
        typedef std::shared_ptr<Lobby> lobbySharedPtr_t;
        typedef std::list<lobbySharedPtr_t>::iterator lobbyIterator_t;

        /**
        * @brief data structure telling what lobbies a LobbyManagerThread should process
        */
        struct Range {
          private:
            std::shared_ptr<SharedLock> rwLock_;

          public:
            lobbyIterator_t start;
            lobbyIterator_t end;

            Range() = default;
            Range(const Range &other);

            /**
            * @brief calls this->unlock()
            */
            ~Range();

            /**
            * @brief calls lock_shared() on the rwMutex_, allowing reading and processing of the lobbies
            */
            void lock(std::shared_ptr<SharedLock> rwLock);

            /**
            * @brief releases ownership of the lobbies
            */
            void unlock() noexcept;
        };

      private:
        const unsigned managerCount_;
        std::shared_ptr<SharedLock> rwLock_;
        std::list<lobbySharedPtr_t> lobbies_;
        std::vector<Range> ranges_;
        LobbyIDGenerator idGenerator_;
        boost::condition_variable_any condVar_;
        bool running_ { true };

        /**
        * @brief dispatches lobbies into this->ranges_
        */
        void dispatch_();

        /**
        * @brief removes dead lobbies from this->lobbies_
        */
        void removeDeadLobbies_();

      public:
        LobbyDispatcher(unsigned managerCount);
        ~LobbyDispatcher() = default;

        /**
        * @brief adds a new lobby to dispatch
        */
        const Lobby &createLobby(std::shared_ptr<Scene> &&scene, const std::string &mapName);

        /**
        * @brief get the range of lobbies to process depending on a LobbyManagerThread's index
        */
        Range dispatch(unsigned managerIndex);

        /**
        * @brief get all the lobbies to read their data
        */
        Range dispatch();

        /**
        * @brief blocks the calling thread until a lobby is created
        */
        void waitForNewLobby();

        void notifyAll();

        void stop();
    };
}
