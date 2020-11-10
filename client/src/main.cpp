/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Client main file
*/

#include <iostream>

#include "engine/core/ecs/entity/Entity.hpp"
#include "engine/core/ecs/entity/EntityManager.hpp"
#include "engine/core/ecs/component/ComponentManager.hpp"
#include "engine/core/ecs/component/Component.hpp"
#include "engine/core/ecs/system/SystemManager.hpp"

using namespace rtype;

class PositionComponent: public Component<PositionComponent>
{
    public:
        int x { 0 };
        int y { 0 };

        PositionComponent() = default;
        PositionComponent(int x, int y)
            : x { x }
            , y { y }
        {};
        ~PositionComponent() = default;
};

class GravityComponent: public Component<GravityComponent>
{
    public:
        double g { 9.81 };

        GravityComponent() = default;
        GravityComponent(double g)
            : g { g }
        {};
        ~GravityComponent() = default;
};

int main(void)
{
    ComponentManager cm;
    EntityManager em(cm);
    SystemManager sm(cm);

    auto player = em.createEntity();
    player->addComponent<PositionComponent>(3, 4);
    player->addComponent<GravityComponent>();

    sm.addSystem<PositionComponent>([&](PositionComponent *position) {
        id_t entityId = position->getEntityId();
        std::cout << position->x << ":" << position->y << std::endl;
        if (cm.hasComponent<GravityComponent>(entityId)) {
            auto gravity = cm.getComponent<GravityComponent>(entityId);
            position->x += gravity->g;
        }
    });

    sm.update();
    return (0);
}