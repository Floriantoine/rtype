/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** ScaleComponent
*/

#include "ScaleComponent.hpp"

namespace rtype::client {

    ScaleComponent::ScaleComponent(float x, float y)
        : x { x }
        , y { y } {};

    void ScaleComponent::factory(const std::shared_ptr<Entity> &entity, nlohmann::json body)
    {
        float x { 0 };
        float y { 0 };

        auto xJson = body.find("x");
        if (xJson != body.end()) {
            xJson->get_to(x);
        }

        auto yJson = body.find("y");
        if (yJson != body.end()) {
            yJson->get_to(y);
        }

        entity->addComponent<ScaleComponent>(x, y);
    }
};