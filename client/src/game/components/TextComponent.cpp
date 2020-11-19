/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** TextComponent
*/

#include "TextComponent.hpp"

#include "engine/core/AssetLoader.hpp"

namespace rtype::client {

    TextComponent::TextComponent(std::string string, std::shared_ptr<sf::Font> font, int size)
        : string { string }
        , font { font }
        , size { size }
        , text(string, *font.get(), size)
    { }

    void TextComponent::factory(const std::shared_ptr<Entity> &entity, nlohmann::json body)
    {
        std::string fontPath { "" };
        int size { 30 };
        std::string string { "" };

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

        entity->addComponent<TextComponent>(
            string,
            AssetLoader::getFont(fontPath),
            size);
    }
};