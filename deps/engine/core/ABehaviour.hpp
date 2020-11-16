/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Behaviour abstract class
*/

#pragma once

#include "./ecs/assert.hpp"
#include "./ecs/entity/Entity.hpp"
#include "./components/BehaviourComponent.hpp"
#include "nlohmann/json.hpp"

#include <memory>

namespace sf {
    class Event;
}

namespace rtype {

    /**
     * Behaviour abstract class
     *
     * Behaviours are entity-specific behaviours
     * Behaviours must inherit from this class to be triggered by the default 
     * systems
     */
    class ABehaviour : public IBehaviour {
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
         * Get the entity the script is attached to
         * 
         * @returns associated entity
         */
        Entity *getEntity() const
        {
            return this->holder_->getEntity();
        }

        /**
         * Get component of type T associated to the Sript's owner entity
         *
         * @tparam T component type
         *
         * @return a component of type T associated to the Sript's owner entity
         */
        template<class T>
        T *getComponent()
        {
            return this->getEntity()->getComponent<T>();
        }

        /**
         * Destroy the Sript's owner entity
         */
        void destroyEntity()
        {
            this->getEntity()->getEntityManager()->destroyEntity(this->getEntity()->getId());
        }

        /**
         * Creates a factory for a ABehaviour derived class
         *
         * @tparam T a ABehaviour derived class
         *
         * @returns a factory for the T class, derived from ABehaviour
         */
        template <class T>
        static auto getFactory()
        {
            STATIC_ASSERT_IS_BASE_OF(ABehaviour, T);
            return [](const std::shared_ptr<Entity> &entity, nlohmann::json body) {
                entity->addComponent<BehaviourComponent>(new T());
                BehaviourComponent *holder = entity->getComponent<BehaviourComponent>();
                ABehaviour *script = reinterpret_cast<ABehaviour *>(holder->getBehaviour());
                script->onInit();
            };
        }
    };

}
