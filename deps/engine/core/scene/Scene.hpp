/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Scene
*/

#pragma once

#include "../ecs/entity/EntityManager.hpp"
#include "../ecs/system/SystemManager.hpp"

namespace rtype {

    class Scene {
      public:
        enum State {
            STATE_RUNNING,
            STATE_PAUSED,
            STATE_INACTIVE
        };

      private:
        static const id_t getNextId()
        {
            static id_t id = 0;
            return id++;
        }

        id_t id_;

        State state_;
        ComponentManager componentManager_;
        EntityManager entityManager_;
        SystemManager systemManager_;

      public:
        Scene()
            : id_ { this->getNextId() }
            , componentManager_()
            , entityManager_(this->componentManager_)
            , systemManager_(this->componentManager_)
        { }

        ~Scene() = default;

        id_t getId() const
        {
            return this->id_;
        }

        void setState(State state)
        {
            this->state_ = state;
        }

        std::shared_ptr<Entity> createEntity()
        {
            return this->entityManager_.createEntity();
        }

        void removeEntity(std::shared_ptr<Entity> entity)
        {
            this->entityManager_.destroyEntity(entity->getId());
        }

        template <class T, typename... Args>
        std::shared_ptr<T> createSystem(Args &&... args)
        {
            return this->systemManager_.createSystem<T>(std::forward(args)...);
        }

        template <class T>
        void removeSystem(std::shared_ptr<T> system)
        {
            this->systemManager_.removeSystem(system);
        }

        void update()
        {
            if (this->state_ == STATE_INACTIVE)
                return;
            this->systemManager_.update();
        }

        void update(ASystem::system_group_e group)
        {
            if (this->state_ == STATE_INACTIVE)
                return;
            this->systemManager_.update(group);
        }
    };

}
