/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Event manager class definition
*/

#pragma once

#include <string>
#include <map>
#include <vector>
#include <functional>
#include <mutex>

#include "engine/utils/Singleton.hpp"
#include "engine/core/events/IEvent.hpp"

namespace rtype
{

/**
 * Event manager, allowing for event binding, unbinding and triggering
 */
class EventManager : public Singleton<EventManager>
{
using listener_t = std::function<void (IEvent *)>;
using map_t = std::multimap<std::string, listener_t>;
using iterator_t = map_t::iterator;

private:
    /**
     * Multimap of event listeners
     */
    map_t _listeners;
    std::mutex mutex;

protected:
	~EventManager() = default;

public:
    /**
     * Bind a listener to an event name
     *
     * @param eventName event name to bind listener to
     * @param listener function called when event is emitted
     */
    static iterator_t on(const std::string &eventName, listener_t listener)
    {
        return EventManager::getInstance()._on(eventName, listener);
    }

    /**
     * Unbind a specific listener
     *
     * @param iterator listener iterator
     */
    static void remove(iterator_t iterator)
    {
        EventManager::getInstance()._remove(iterator);
    }

    /**
     * Emit an event, triggering all associated listeners
     *
     * @param eventName event name to trigger
     * @param event event data
     */
    static void emit(const std::string &eventName, IEvent *event)
    {
        EventManager::getInstance()._emit(eventName, event);
    }

private:
    iterator_t _on(const std::string &eventName, listener_t listener)
    {
        std::lock_guard<std::mutex> lock(mutex);
        return _listeners.insert({ eventName, listener });
    }

    void _remove(iterator_t iterator)
    {
        std::lock_guard<std::mutex> lock(mutex);
        _listeners.erase(iterator);
    }

    void _emit(const std::string &eventName, IEvent *event)
    {
        auto range = _listeners.equal_range(eventName);

        for (auto &it = range.first; it != range.second; ++it) {
            it->second(event);
        }
    }
};

}