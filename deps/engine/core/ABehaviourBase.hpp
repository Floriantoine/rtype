/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Behaviour abstract base class
*/

#pragma once

#include "./components/BehaviourComponent.hpp"
#include "./components/HealthComponent.hpp"
#include "./ecs/assert.hpp"
#include "./ecs/entity/Entity.hpp"
#include "./ecs/entity/EntityManager.hpp"
#include "./physics/CollisionData.hpp"
#include "nlohmann/json.hpp"

#include <iostream>
#include <memory>

namespace rtype {

    /**
     * Behaviour abstract base class
     *
     * Behaviours are entity-specific behaviours
     * Behaviours must inherit from this class to be triggered by the default 
     * systems
     */
    class ABehaviourBase : public IBehaviour {
      public:
        /**
         * Method called when behaviour component is initialized
         */
        virtual void onInit() {};

        /**
         * Method called on every game update
         */
        virtual void onUpdate(long elapsedTime) = 0;

        /**
         * Method called when the behaviour's entity is destroyed
         */
        virtual void onDestroy() {};

        /**
         * Method called when the associated entity collides with another entity
         */
        virtual void onCollide(const CollisionData &collision) {};

        /**
         * Method called when the entity enters camera view
         */
        virtual void onViewEnter() {};

        /**
         * Method called when the entity leaves camera view
         */
        virtual void onViewLeave() {};

        /**
         * Get the behaviour's entity
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
        template <class T>
        T *getComponent()
        {
            return this->getEntity()->getComponent<T>();
        }

        /**
         * Destroy the Sript's owner entity
         */
        void destroyEntity()
        {
            this->onDestroy();
            this->getEntity()->getEntityManager()->destroyEntity(this->getEntity()->getId());
        }

        /**
         * Get the entity's health points
         * 
         * @returns the entity's health points
         */
        int getHealth()
        {
            HealthComponent *health = this->getComponent<HealthComponent>();
            if (health == nullptr) {
                return 0;
            }
            return health->health;
        }

        /**
         * Make the entity's health component value decrease by [damage]
         * 
         * @param damage damage value to be withdrawn to health value
         */
        void takeDamage(int damage)
        {
            HealthComponent *health = this->getComponent<HealthComponent>();
            if (health == nullptr) {
                std::cerr << "warn: attempting to provide damage, but entity has no HealthComponent" << std::endl;
                return;
            }
            health->health -= damage;
        }

        /**
         * Creates a factory for a ABehaviourBase derived class
         *
         * @tparam T a ABehaviourBase derived class
         *
         * @returns a factory for the T class, derived from ABehaviourBase
         */
        template <class T>
        static auto getFactory()
        {
            STATIC_ASSERT_IS_BASE_OF(ABehaviourBase, T);
            return [](const std::shared_ptr<Entity> &entity, const nlohmann::json &body) {
                entity->addComponent<BehaviourComponent>(std::make_shared<T>());
                auto *holder = entity->getComponent<BehaviourComponent>();
                std::shared_ptr<ABehaviourBase> script = holder->getBehaviour<ABehaviourBase>();
                script->onInit();
            };
        }
    };
}
