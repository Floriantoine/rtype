#include <catch2/catch.hpp>

#include "engine/core/ecs/component/Component.hpp"
#include "engine/core/ecs/entity/Entity.hpp"

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

TEST_CASE("components can be added and retrieved from entities", "[entity]")
{
    Entity entity;

    SECTION("a component can be added to an entity") {
        entity.addComponent<PositionComponent>(13, 37);
        REQUIRE(entity.hasComponent<PositionComponent>() == true);

        auto position = entity.getComponent<PositionComponent>();
        REQUIRE((position->x == 13 && position->y == 37));
    }

    SECTION("multiple components can be added to an entity") {
        entity.addComponent<PositionComponent>(13, 37);
        entity.addComponent<GravityComponent>(9.81);
        REQUIRE(entity.hasComponent<PositionComponent>() == true);
        REQUIRE(entity.hasComponent<GravityComponent>() == true);

        auto gravity = entity.getComponent<GravityComponent>();
        REQUIRE(gravity->g == 9.81);
    }

    SECTION("a component can be removed from an entity") {
        entity.addComponent<PositionComponent>(13, 37);
        REQUIRE(entity.hasComponent<PositionComponent>() == true);
        entity.removeComponent<PositionComponent>();
        REQUIRE(entity.hasComponent<PositionComponent>() == false);
    }

    SECTION("multiple components can be removed from an entity") {
        entity.addComponent<PositionComponent>(13, 37);
        entity.addComponent<GravityComponent>();
        REQUIRE(entity.hasComponent<PositionComponent>() == true);
        REQUIRE(entity.hasComponent<GravityComponent>() == true);
        entity.removeComponent<PositionComponent>();
        REQUIRE(entity.hasComponent<PositionComponent>() == false);
        REQUIRE(entity.hasComponent<GravityComponent>() == true);
        entity.removeComponent<GravityComponent>();
        REQUIRE(entity.hasComponent<GravityComponent>() == false);
    }
}
