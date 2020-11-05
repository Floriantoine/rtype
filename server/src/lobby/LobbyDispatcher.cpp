/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** LobbyDispatcher
*/

#include "LobbyDispatcher.hpp"

#include <atomic>
#include <optional>
#include <vector>

namespace RType {
    LobbyDispatcher::Range::Range(DataLock<unsigned> &readingCount)
        : readingCount_(readingCount)
    {
        this->readingCount_.apply([](unsigned &val) {
            ++val;
        });
    }

    LobbyDispatcher::Range::~Range()
    {
        this->release();
    }

    void LobbyDispatcher::Range::release()
    {
        if (!this->released_) {
            this->readingCount_.apply([](unsigned &val) {
                --val;
            });
            this->released_ = true;
            this->start = iterator_t();
            this->end = iterator_t();
        }
    }

    LobbyDispatcher::LobbyDispatcher(unsigned managerCount)
        : managerCount_ { managerCount }
    {
    }

    void LobbyDispatcher::emplaceBack(LobbyDispatcher::lobbyPtr_t &lobby)
    {
        this->needWritting_ = true;
        auto lock = this->readingCount_.wait([](const unsigned &val) {
            return val == 0;
        });
        this->lobbies_.emplace_back(std::move(lobby));
        this->needWritting_ = false;
    }

    LobbyDispatcher::iterator_t LobbyDispatcher::remove(LobbyDispatcher::iterator_t it)
    {
        this->needWritting_ = true;
        auto lock = this->readingCount_.wait([](const unsigned &val) {
            return val == 0;
        });
        return this->lobbies_.erase(it);
    }

    LobbyDispatcher::Range LobbyDispatcher::dispatch(unsigned managerIndex)
    {
        // TODO
        return Range(this->readingCount_);
    }
}