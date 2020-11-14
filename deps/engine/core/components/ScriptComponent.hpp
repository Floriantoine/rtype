/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** ATextureComponent
*/

#pragma once

#include "../ecs/component/Component.hpp"

namespace rtype {

    class ScriptComponent : public Component<ScriptComponent> {
      public:
        ScriptComponent() = default;
    };
}