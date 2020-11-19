/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** AnimationComponent
*/

#include "AnimationComponent.hpp"

namespace rtype::client {

    AnimationComponent::AnimationComponent(int currentFrame, int totalFrame, long rate)
        : currentFrame { currentFrame }
        , totalFrame { totalFrame }
        , rate { rate } {};

    void AnimationComponent::factory(const std::shared_ptr<Entity> &entity, nlohmann::json body)
    {
        int currentFrame { 0 };
        int totalFrame { 0 };
        long rate { 0 };

        auto currentJson = body.find("currentFrame");
        if (currentJson != body.end()) {
            currentJson->get_to(currentFrame);
        }
        auto totalJson = body.find("totalFrame");
        if (totalJson != body.end()) {
            totalJson->get_to(totalFrame);
        }
        auto rateJson = body.find("rate");
        if (rateJson != body.end()) {
            rateJson->get_to(rate);
        }

        entity->addComponent<AnimationComponent>(currentFrame, totalFrame, rate);
    }
};