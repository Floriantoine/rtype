/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** LobbyManagerThread
*/

#include "LobbyManagerThread.hpp"

#include "utils/Clock.hpp"

#include <chrono>
#include <iostream>
#include <optional>
#include <thread>
#include <utility>

namespace rtype::server {
    unsigned LobbyManagerThread::Index_ = 0;

    LobbyManagerThread::LobbyManagerThread(std::shared_ptr<LobbyDispatcher> dispatcher)
        : dispatcher_ { dispatcher }
        , index_(Index_)
        , thread_([&] {
            this->run_();
        })
    {
        ++this->Index_;
    }

    LobbyManagerThread::~LobbyManagerThread()
    {
        this->dispatcher_->stop();
        this->isRunning_ = false;
        this->dispatcher_->notifyAll();
        this->thread_.join();
    }

    void LobbyManagerThread::run_()
    {
        while (this->isRunning_) {
            auto expectedEnd = Clock::Now() + TICK_TIME;
            this->onTick_();
            std::this_thread::sleep_until(expectedEnd);
        }
    }

    void LobbyManagerThread::onTick_() const
    {
        if (this->shouldWait_) {
            this->dispatcher_->waitForNewLobby();
        }
        LobbyDispatcher::Range range = this->dispatcher_->dispatch(this->index_);

        this->shouldWait_ = range.start == range.end;
        for (; range.start != range.end; ++range.start) {
            (*range.start)->onTick();
        }
    }
}
