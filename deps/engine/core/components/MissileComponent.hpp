/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** ATextureComponent
*/

#pragma once

#include "engine/core/ecs/component/Component.hpp"
#include <string>

namespace rtype {

    class MissileComponent : public Component<MissileComponent>
    {
    public:
        std::string missileType { "" };
        std::size_t rate { 0 };

    public:
        MissileComponent() = default;
        MissileComponent(std::string missileType, std::size_t rate) :
        missileType { missileType }, rate { rate } {};
    };
}