/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** ATextureComponent
*/

#pragma once

#include "../Rect.hpp"
#include "../ecs/component/Component.hpp"
#include "../ecs/entity/Entity.hpp"
#include "nlohmann/json.hpp"

#include <memory>

namespace rtype {

    class CollideBoxComponent : public Component<CollideBoxComponent> {
      public:
        Rect<float> box;

      public:
        CollideBoxComponent() = default;
        CollideBoxComponent(float left, float top, float width, float height)
            : box(left, top, width, height)
        { }

        static void factory(const std::shared_ptr<Entity> &entity, nlohmann::json body)
        {
            float left { 0 };
            float top { 0 };
            float width { 0 };
            float height { 0 };

            auto xJson = body.find("left");
            if (xJson != body.end()) {
                xJson->get_to(left);
            }
            auto yJson = body.find("top");
            if (yJson != body.end()) {
                yJson->get_to(top);
            }
            auto wJson = body.find("width");
            if (wJson != body.end()) {
                wJson->get_to(width);
            }
            auto hJson = body.find("height");
            if (hJson != body.end()) {
                hJson->get_to(height);
            }

            entity->addComponent<CollideBoxComponent>(left, top, width, height);
        }
    };
}