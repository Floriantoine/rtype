/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** LobbyDispatcher
*/

#include "LobbyDispatcher.hpp"

#include "Lobby.hpp"
#include "Exception.hpp"

#include <atomic>
#include <memory>
#include <optional>
#include <vector>

namespace rtype::server {
    LobbyDispatcher::Range::Range(const Range &other)
        : rwMutex_(other.rwMutex_)
        , start(other.start)
        , end(other.end)
    {
    }

    LobbyDispatcher::Range::~Range()
    {
        this->unlock();
    }

    void LobbyDispatcher::Range::lock(std::shared_ptr<std::shared_mutex> rwMutex) noexcept
    {
        this->rwMutex_ = rwMutex;

        if (this->rwMutex_ != nullptr) {
            this->rwMutex_->lock_shared();
        }
    }

    void LobbyDispatcher::Range::unlock() noexcept
    {
        if (this->rwMutex_ != nullptr) {
            this->rwMutex_->unlock_shared();
            this->start = lobbyIterator_t();
            this->end = lobbyIterator_t();
            this->rwMutex_.reset();
        }
    }

    LobbyDispatcher::LobbyDispatcher(unsigned managerCount)
        : rwMutex_(std::make_shared<std::shared_mutex>())
        , managerCount_ { managerCount }
    {
        if (this->managerCount_ == 0) {
            throw Exception("LobbyDispatcher::LobbyDispatcher managerCount of 0 isn't valid");
        }
        this->dispatch_();
    }

    void LobbyDispatcher::dispatch_()
    {
        auto share = this->lobbies_.size() / this->managerCount_;
        auto leftover = this->lobbies_.size() % this->managerCount_;
        auto it = this->lobbies_.begin();

        this->lobbies_.clear();
        for (auto i = 0u; i < this->managerCount_; ++i) {
            auto &range = this->ranges_.emplace_back();
            range.start = it;
            for (auto n = 0u; n < share + (leftover != 0); ++n) {
                ++it;
            }
            leftover -= leftover != 0;
            range.end = it;
        }
    }

    void LobbyDispatcher::removeDeadLobbies_()
    {
        bool locked = false;
        auto it = this->lobbies_.begin();

        while (it != this->lobbies_.end()) {
            if ((*it)->isRunning()) {
                ++it;
            } else {
                if (!locked) {
                    (*this->needWrite_) = true;
                    this->rwMutex_->lock();
                    locked = true;
                }
                it = this->lobbies_.erase(it);
            }
        }
        if (locked) {
            this->dispatch_();
            this->rwMutex_->unlock();
            (*this->needWrite_) = false;
            this->needWrite_.notify_all();
        }
    }

    void LobbyDispatcher::emplaceBack(LobbyDispatcher::lobbyUniquePtr_t &lobby)
    {
        bool restart = true;
        std::string id;

        (*this->needWrite_) = true;
        this->rwMutex_->lock();
        while (restart) {
            restart = false;
            id = this->idGenerator_();
            for (const auto &it : this->lobbies_) {
                if (it->id == id) {
                    restart = true;
                    break;
                }
            }
        }
        lobby->id = id;
        this->lobbies_.emplace_back(std::move(lobby));
        this->dispatch_();
        this->rwMutex_->unlock();
        (*this->needWrite_) = false;
        this->needWrite_.notify_all();
    }

    LobbyDispatcher::Range LobbyDispatcher::dispatch(unsigned managerIndex)
    {
        this->needWrite_.wait([](bool val) {
            return val == false;
        });
        removeDeadLobbies_();
        Range range(this->ranges_.at(managerIndex));
        range.lock(this->rwMutex_);
        return range;
    }
}