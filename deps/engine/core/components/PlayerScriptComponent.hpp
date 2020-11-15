/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Player Script Component
*/

#pragma once

#include "./AScriptComponent.hpp"

namespace rtype {

    class PlayerScriptComponent : public AScriptComponent {
      public:
        void onInit() override
        {
            std::cout << "player init" << std::endl;
        }

        void onUpdate() override
        {
            std::cout << "player update" << std::endl;
        }

        void onKeyboardInput() override
        {
        }

        void onCollide() override
        {
        }
    };

}
