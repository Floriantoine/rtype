/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Event manager implementation
*/

#include "engine/core/events/EventManager.hpp"

namespace rtype
{

EventManager::iterator_t EventManager::on(const std::string &eventName, listener_t listener)
{
    return EventManager::getInstance()._on(eventName, listener);
}

void EventManager::remove(iterator_t iterator)
{
    EventManager::getInstance()._remove(iterator);
}

void EventManager::emit(const std::string &eventName, IEvent *event)
{
    EventManager::getInstance()._emit(eventName, event);
}

EventManager::iterator_t EventManager::_on(const std::string &eventName, listener_t listener)
{
    std::lock_guard<std::mutex> lock(mutex);
    return _listeners.insert({ eventName, listener });
}

void EventManager::_remove(iterator_t iterator)
{
    std::lock_guard<std::mutex> lock(mutex);
    _listeners.erase(iterator);
}

void EventManager::_emit(const std::string &eventName, IEvent *event)
{
    auto range = _listeners.equal_range(eventName);

    for (auto &it = range.first; it != range.second; ++it) {
        it->second(event);
    }
}

}