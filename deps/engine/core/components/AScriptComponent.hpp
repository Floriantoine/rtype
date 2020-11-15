/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** ScriptComponent
*/

#pragma once

#include "../ecs/assert.hpp"
#include "../ecs/component/Component.hpp"
#include "../ecs/entity/Entity.hpp"
#include "nlohmann/json.hpp"

#include <memory>

namespace sf {
    class Event;
}

namespace rtype {

    /**
     * Script component abstract class
     *
     * Scripts are entity-specific behaviors
     * Scripts must inherit from this class to be triggered by the default 
     * systems
     */
    class AScriptComponent : public Component<AScriptComponent> {
      public:
        /**
         * Method called when script component is initialized
         */
        virtual void onInit() {};

        /**
         * Method called on every game update
         */
        virtual void onUpdate(long elapsedTime) = 0;

        /**
         * Method called when the associated entity collides with another entity
         */
        virtual void onCollide() {};

        /**
         * Method called when a keyboard key is pressed
         */
        virtual void onKeyPressed(const sf::Event &) {};

        /**
         * Method called when a keyboard key is released
         */
        virtual void onKeyReleased(const sf::Event &) {};

        /**
         * Method called when a mouse button is pressed
         */
        virtual void onMouseButtonPressed(const sf::Event &) {};

        /**
         * Method called when a mouse button is released
         */
        virtual void onMouseButtonReleased(const sf::Event &) {};

        /**
         * Creates a factory for a ScriptComponent derived class
         *
         * @tparam T a ScriptComponent derived class
         *
         * @returns a factory for the T class, derived from ScriptComponent
         */
        template <class T>
        static auto getFactory()
        {
            return [](const std::shared_ptr<Entity> &entity, nlohmann::json body) {
                STATIC_ASSERT_IS_BASE_OF(AScriptComponent, T);
                entity->addComponent<T>();
                entity->getComponent<T>()->onInit();
            };
        }
    };

}
