/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** LobbyDispatcher
*/

#include "LobbyDispatcher.hpp"

#include "Exception.hpp"
#include "Lobby.hpp"

#include <atomic>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace rtype::server {
    LobbyDispatcher::Range::Range(const Range &other)
        : rwLock_(other.rwLock_)
        , start(other.start)
        , end(other.end)
    {
    }

    LobbyDispatcher::Range::~Range()
    {
        this->unlock();
    }

    void LobbyDispatcher::Range::lock(const std::shared_ptr<SharedLock> &rwLock)
    {
        this->rwLock_ = rwLock;

        if (this->rwLock_ != nullptr) {
            this->rwLock_->lock_shared();
        }
    }

    void LobbyDispatcher::Range::unlock() noexcept
    {
        if (this->rwLock_ != nullptr) {
            this->rwLock_->unlock_shared();
            this->start = lobbyIterator_t();
            this->end = lobbyIterator_t();
            this->rwLock_ = nullptr;
        }
    }

    LobbyDispatcher::LobbyDispatcher(unsigned managerCount)
        : rwLock_(std::make_shared<SharedLock>())
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

        this->ranges_.clear();
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
                    this->rwLock_->lock();
                    locked = true;
                }
                it = this->lobbies_.erase(it);
            }
        }
        if (locked) {
            this->dispatch_();
            this->rwLock_->unlock();
        }
    }

    const Lobby &LobbyDispatcher::createLobby(std::shared_ptr<Scene> &&scene, const std::string &mapName)
    {
        bool restart = true;
        std::string id;

        this->rwLock_->lock();
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
        std::shared_ptr<Lobby> &lobby = this->lobbies_.emplace_back(std::make_shared<Lobby>(id, std::move(scene), mapName));
        this->dispatch_();
        this->rwLock_->unlock();
        this->condVar_.notify_one();
        return *lobby;
    }

    LobbyDispatcher::Range LobbyDispatcher::dispatch(unsigned managerIndex)
    {
        removeDeadLobbies_();

        Range range(this->ranges_.at(managerIndex));
        range.lock(this->rwLock_);
        return range;
    }

    LobbyDispatcher::Range LobbyDispatcher::dispatch()
    {
        removeDeadLobbies_();

        Range range;
        range.start = this->lobbies_.begin();
        range.end = this->lobbies_.end();
        range.lock(this->rwLock_);
        return range;
    }

    void LobbyDispatcher::waitForNewLobby()
    {
        if (!this->running_)
            return;
        auto slock = this->rwLock_->shared_lock();
        this->condVar_.wait(slock);
    }

    void LobbyDispatcher::notifyAll()
    {
        this->condVar_.notify_all();
    }

    void LobbyDispatcher::stop()
    {
        this->running_ = false;
    }
}
