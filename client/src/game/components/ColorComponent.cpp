/*
** EPITECH PROJECT, 2020
** *
** File description:
** ColorComponent
*/

#include "ColorComponent.hpp"

namespace rtype::client {

    ColorComponent::ColorComponent(int red, int green, int blue, int alpha, bool outline)
        : red { red }
        , green { green }
        , blue { blue }
        , alpha { alpha }
        , outline { outline }
        , color(red, green, blue, alpha) {};

    void ColorComponent::factory(const std::shared_ptr<Entity> &entity, nlohmann::json body)
    {
        int red { 0 };
        int green { 0 };
        int blue { 0 };
        int alpha { 255 };
        bool outline { false };

        auto redJson = body.find("red");
        if (redJson != body.end()) {
            redJson->get_to(red);
        }

        auto greenJson = body.find("green");
        if (greenJson != body.end()) {
            greenJson->get_to(green);
        }

        auto blueJson = body.find("blue");
        if (blueJson != body.end()) {
            blueJson->get_to(blue);
        }

        auto alphaJson = body.find("alpha");
        if (alphaJson != body.end()) {
            alphaJson->get_to(alpha);
        }

        auto outlineJson = body.find("outline");
        if (outlineJson != body.end()) {
            outlineJson->get_to(outline);
        }

        entity->addComponent<ColorComponent>(red, blue, green, alpha, outline);
    }
};
