/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Client main file
*/
#include "engine/core/Game.hpp"
#include "engine/core/ecs/component/Component.hpp"
#include "engine/core/ecs/system/ASystem.hpp"

#include <iostream>

using namespace rtype;

class PositionComponent : public Component<PositionComponent> {
  public:
    int x { 0 };
    int y { 0 };

    PositionComponent() = default;
    PositionComponent(int x, int y)
        : x { x }
        , y { y }
    { }
};

class ARenderSystem : public ASystem {
  protected:
    ARenderSystem()
        : ASystem(ASystem::RENDER_SYSTEM_GROUP)
    { }
};

class SpriteSystem : public ARenderSystem {
    void update() override
    {
        std::cout << "Updating sprite system" << std::endl;
    }
};

class PositionSystem : public ASystem {
  public:
    void update() override
    {
        std::cout << "Updating position system" << std::endl;
    }
};

int main(int ac, char *av[])
{
    Game game;

    auto scene = game.createScene(0);
    auto player = scene->createEntity();
    player->addComponent<PositionComponent>();

    scene->createSystem<PositionSystem>();
    scene->createSystem<SpriteSystem>();

    game.run();
    return 0;
}
