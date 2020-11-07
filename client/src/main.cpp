#include <iostream>

#include "engine/core/ecs/entity/Entity.hpp"
#include "engine/core/ecs/component/ComponentManager.hpp"
#include "engine/core/ecs/component/Component.hpp"
#include "engine/core/ecs/system/SystemManager.hpp"

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
    ComponentManager &cm = ComponentManager::getInstance();
    SystemManager &sm = SystemManager::getInstance();
    
    Entity player;

    player.addComponent<PositionComponent>(3, 4);
    player.addComponent<GravityComponent>();

    sm.addSystem<PositionComponent>([&](PositionComponent *position) {
        id_t entityId = position->getEntityId();
        std::cout << position->x << ":" << position->y << std::endl;
        if (cm.hasComponent<GravityComponent>(entityId)) {
            auto gravity = cm.getComponent<GravityComponent>(entityId);
            position->x += gravity->g;
        }
    });

    sm.update();
}
