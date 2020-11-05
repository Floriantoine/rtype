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

namespace RType {
    LobbyManagerThread::LobbyManagerThread(std::shared_ptr<LobbyDispatcher> dispatcher, unsigned index)
        : dispatcher_ { dispatcher }
        , index_ { index }
        , thread_([&] {
            this->run();
        })
    {
    }

    LobbyManagerThread::~LobbyManagerThread()
    {
        isRunning_ = false;
        this->thread_.join();
    }

    void LobbyManagerThread::run()
    {
        this->isRunning_ = true;
        while (this->isRunning_) {
            auto expectedEnd = Clock::now() + TICK_TIME;
            this->onTick_();
            std::this_thread::sleep_until(expectedEnd);
        }
    }

    void LobbyManagerThread::onTick_()
    {
        auto range = this->dispatcher_->dispatch(this->index_);

        for (; range.start != range.end; ++range.start) {
            (*range.start)->onTick();
        }
    }
}