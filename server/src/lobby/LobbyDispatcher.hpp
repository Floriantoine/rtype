/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** LobbyDispatcher
*/

#pragma once

#include "Lobby.hpp"
#include "utils/DataLock.hpp"

#include <atomic>
#include <memory>
#include <optional>
#include <vector>

namespace RType {
    class LobbyDispatcher {
      public:
        typedef std::unique_ptr<Lobby> lobbyPtr_t;
        typedef std::vector<lobbyPtr_t>::iterator iterator_t;

        struct Range {
            friend class LobbyDispatcher;

          private:
            bool released_ { false };
            DataLock<unsigned> &readingCount_;

            Range(DataLock<unsigned> &readingCount);

          public:
            iterator_t start;
            iterator_t end;

            ~Range();
            void release();
        };

      private:
        const unsigned managerCount_;
        bool needWritting_ { false };
        DataLock<unsigned> readingCount_ { 0 };
        DataLock<bool> isWritting_ { false };
        std::vector<lobbyPtr_t> lobbies_;

      public:
        LobbyDispatcher(unsigned managerCount);
        ~LobbyDispatcher() = default;

        void emplaceBack(lobbyPtr_t &lobby);
        iterator_t remove(iterator_t it);
        Range dispatch(unsigned managerIndex);
    };
}
