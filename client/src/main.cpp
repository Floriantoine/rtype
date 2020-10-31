#include <iostream>

#include "engine/core/events/EventManager.hpp"
#include "engine/core/events/MouseEvent.hpp"
#include <thread>

int main(void)
{
    std::thread t1([]() {
        auto it1 = EventManager::on("click", [](IEvent *) { std::cout << "Thread1/Listener 1" << std::endl; });
        auto it2 = EventManager::on("click", [](IEvent *) { std::cout << "Thread1/Listener 2" << std::endl; });
    });
    std::thread t2([]() {
        auto it3 = EventManager::on("click", [](IEvent *) { std::cout << "Thread2/Listener 1" << std::endl; });
        EventManager::remove(it3);
        auto it4 = EventManager::on("click", [](IEvent *) { std::cout << "Thread2/Listener 2" << std::endl; });
    });
    t1.join();
    t2.join();
    EventManager::emit("click", nullptr);
}
