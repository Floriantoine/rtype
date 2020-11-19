/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** NavDirectionComponent
*/

#include "NavDirectionComponent.hpp"

namespace rtype::client {

    NavDirectionComponent::NavDirectionComponent(const std::string &direction)
        : direction { direction }
    { }

    void NavDirectionComponent::factory(const std::shared_ptr<Entity> &entity, const nlohmann::json &body)
    {
        std::string direction;

        auto directionJson = body.find("direction");
        if (directionJson != body.end()) {
            directionJson->get_to(direction);
        }

        entity->addComponent<NavDirectionComponent>(direction);
    }
};