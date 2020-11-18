/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** System class
*/

#pragma once

#include "../component/ComponentManager.hpp"
#include "../types.hpp"
#include "../../components/CameraComponent.hpp"

#include <iostream>

namespace rtype {

    class ASystem {
        friend class SystemManager;

      public:
        enum system_group_e {
            UNKNOWN_SYSTEM_GROUP = -1,
            RENDER_SYSTEM_GROUP
        };

      private:
        system_group_e group_;

      protected:
        ComponentManager *componentManager_;

        ASystem(system_group_e group = UNKNOWN_SYSTEM_GROUP)
            : group_ { group }
        { }
        ~ASystem() = default;

        Entity *getCamera() const
        {
            static Entity *camera = nullptr;

            if (camera == nullptr) {
                int cameraCount = 0;
                this->componentManager_->apply<CameraComponent>([&](CameraComponent *cameraComponent) {
                    ++cameraCount;
                    if (cameraCount > 1)
                        return;
                    camera = cameraComponent->getEntity();
                });
                if (cameraCount == 0) {
                    std::cerr << "warn: no scene camera defined" << std::endl;
                } else if (cameraCount > 1) {
                    std::cerr << "warn: more than 1 scene camera defined. Only 1 will be used" << std::endl;
                }
            }
            return camera;
        }

      public:
        virtual void update(long elapsedTime) = 0;

        system_group_e getGroup()
        {
            return this->group_;
        }
    };

}
