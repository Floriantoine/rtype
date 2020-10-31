#include <iostream>

#include "engine/core/events/EventManager.hpp"
#include "engine/core/events/MouseEvent.hpp"

int main(void)
{
    int toto = 3;
    auto listener1 = [](IEvent *e) { std::cout << "Listener 1" << std::endl; };
    auto listener2 = [](IEvent *e) { std::cout << "Listener 2" << std::endl; };

    auto it1 = EventManager::on("click", listener1);
    auto it2 = EventManager::on("click", listener2);
    auto it3 = EventManager::on("click", listener2);
    EventManager::emit("click", nullptr);
}
