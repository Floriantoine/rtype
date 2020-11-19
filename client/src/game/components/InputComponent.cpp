/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** InputComponent
*/

#include "InputComponent.hpp"

#include "engine/core/AssetLoader.hpp"

namespace rtype::client {

    InputComponent::InputComponent(std::string string, std::shared_ptr<sf::Font> font, int size, Vector2<float> offset, int max)
        : string { string }
        , font { font }
        , size { size }
        , offset { offset }
        , text(string, *font.get(), size)
        , max { max }
    { }

    void InputComponent::factory(const std::shared_ptr<Entity> &entity, const nlohmann::json &body)
    {
        std::string fontPath { "" };
        int size { 30 };
        std::string string { "" };
        float x { 0 };
        float y { 0 };
        int max { 0 };

        auto fontPathJson = body.find("font");
        if (fontPathJson != body.end()) {
            fontPathJson->get_to(fontPath);
        }
        auto sizeJson = body.find("size");
        if (sizeJson != body.end()) {
            sizeJson->get_to(size);
        }
        auto stringJson = body.find("string");
        if (stringJson != body.end()) {
            stringJson->get_to(string);
        }
        auto xJson = body.find("x");
        if (xJson != body.end()) {
            xJson->get_to(x);
        }
        auto yJson = body.find("y");
        if (yJson != body.end()) {
            yJson->get_to(y);
        }
        auto maxJson = body.find("max");
        if (maxJson != body.end()) {
            maxJson->get_to(max);
        }

        entity->addComponent<InputComponent>(
            string,
            AssetLoader::getFont(fontPath),
            size,
            Vector2<float>(x, y),
            max);
    }
};