/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** RenderSystem
*/

#include "core/systems/ARenderSystem.hpp"

namespace rtype::client {
    class BackgroundSystem : public ARenderSystem {
      public:
        BackgroundSystem() = default;
        ~BackgroundSystem() = default;

        void update(long elapsedTime) override;
    };
}