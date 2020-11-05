/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** LobbyDispatcher
*/

#pragma once

#include "Lobby.hpp"
#include "utils/DataLock.hpp"

#include <list>
#include <memory>
#include <queue>
#include <shared_mutex>
#include <vector>

namespace rtype::server {

    /**
    * @brief LobbyManagerThread instances get their lobbies from this class, which holds all lobbies
    */
    class LobbyDispatcher {
      public:
        typedef std::unique_ptr<Lobby> lobbyUniquePtr_t;
        typedef std::list<lobbyUniquePtr_t>::iterator lobbyIterator_t;

        /**
        * @brief data structure telling what lobbies a LobbyManagerThread should process
        */
        struct Range {
          private:
            std::shared_ptr<std::shared_mutex> rwMutex_;

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
            void lock(std::shared_ptr<std::shared_mutex> rwMutex) noexcept;

            /**
            * @brief releases ownership of the lobbies
            */
            void unlock() noexcept;
        };

      private:
        std::shared_ptr<std::shared_mutex> rwMutex_;
        const unsigned managerCount_;
        DataLock<bool> needWrite_ { false };
        std::list<lobbyUniquePtr_t> lobbies_;
        std::vector<Range> ranges_;

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
        void emplaceBack(lobbyUniquePtr_t &lobby);

        /**
        * @brief get the range of lobbies to process depending on a LobbyManagerThread's index
        */
        Range dispatch(unsigned managerIndex);
    };
}
