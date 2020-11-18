/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** SceneLoader
*/

#pragma once

#include "../engine/core/AGame.hpp"
#include "../engine/core/ecs/component/ComponentBase.hpp"
#include "../engine/core/ecs/entity/Entity.hpp"
#include "../engine/core/ecs/entity/EntityManager.hpp"
#include "../engine/core/scene/Scene.hpp"
#include "../engine/core/scene/SceneManager.hpp"
#include "../utils/Singleton.hpp"
#include "nlohmann/json.hpp"
#include "utils/Exception.hpp"
#include "utils/Singleton.hpp"

#include <cstdint>
#include <fstream>
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

namespace rtype {

    class JsonLoader : public Singleton<JsonLoader> {
      public:
        class Exception : public rtype::Exception {
          public:
            Exception(const std::string &msg)
                : rtype::Exception("JsonLoader exception: " + msg)
            { }
            Exception(std::string &&msg)
                : rtype::Exception("JsonLoader exception: " + std::move(msg))
            { }
            virtual ~Exception() override = default;
        };

      private:
        struct JsonUtil {
            static const auto JsonAt(const nlohmann::json &json, const std::string &key, const std::string &errorContext = "")
            {
                const auto &value = json.find(key);
                if (value == json.end())
                    throw Exception("expected `" + key + "` " + errorContext);
                return value;
            }

            static nlohmann::json loadFile(const std::string &file)
            {
                std::ifstream fd(file);

                if (!fd.good()) {
                    return nlohmann::json::value_t::discarded;
                }
                return nlohmann::json::parse(fd, nullptr, false, true);
            }
        };

        class EntityDefinition {
          public:
            std::unordered_map<std::string, nlohmann::json> components;

            EntityDefinition &operator=(const EntityDefinition &other)
            {
                this->components = other.components;
                return *this;
            }

            void addComponent(const nlohmann::json &body)
            {
                const auto &typeJson = JsonUtil::JsonAt(body, "type", "for an object of type `component`");
                const std::string &type = typeJson->get<std::string>();
                this->components[typeJson->get<std::string>()] = body;
            }

            void mergeComponents(const nlohmann::json &json)
            {
                for (const auto &component : json) {
                    std::string type = JsonUtil::JsonAt(component, "type")->get<std::string>();
                    this->components[type].merge_patch(component);
                }
            }
        };

        typedef std::function<void(const std::shared_ptr<Entity> &, const nlohmann::json &)> component_factory_t;

        std::unordered_map<std::string, component_factory_t> factories_;
        std::unordered_map<std::string, EntityDefinition> definitions_;

        const auto getDefinition_(const std::string &key, bool throwOnError = true)
        {
            const auto def = this->definitions_.find(key);
            if (throwOnError && def == this->definitions_.end())
                throw Exception("no defintion found for " + key);
            return (def);
        }

        void loadState_(Scene &scene, const nlohmann::json &json)
        {
            static const std::unordered_map<std::string, Scene::State> States = {
                { "INACTIVE", Scene::STATE_INACTIVE },
                { "RUNNING", Scene::STATE_RUNNING },
                { "PAUSED", Scene::STATE_PAUSED }
            };

            const auto &stateJson = JsonUtil::JsonAt(json, "state");
            const auto &stateStr = stateJson->get<std::string>();
            const auto &state = States.find(stateStr);

            if (state == States.cend()) {
                throw Exception("value `" + stateStr + "` for `state` isn't valid");
            }
            scene.setState(state->second);
        }

      public:
        /**
         * Register a component factory for later use
         * 
         * @param type component factory name (for consistency, choose the component's class name)
         * @param factory factory function to register
         * 
         * @throw
         */
        static void registerComponentFactory(const std::string &type, component_factory_t factory)
        {
            JsonLoader::getInstance().factories_[type] = factory;
        }

        /**
         * Load entities definitions from file
         * 
         * @param file path to the file to load the definitions from
         * 
         * @throw
         */
        static void loadDefinitions(const std::string &file)
        {
            nlohmann::json json = JsonUtil::loadFile(file);

            if (json.is_discarded()) {
                throw Exception("parsing error");
            }

            auto defs = json.find("definitions");
            for (const auto &it : *defs) {
                const auto &id = JsonUtil::JsonAt(it, "id", "for an object of type `definition`")->get<std::string>();
                const auto &check = JsonLoader::getInstance().getDefinition_(id, false);
                if (check != JsonLoader::getInstance().definitions_.cend()) {
                    throw Exception("multiple definition of `" + id + "`");
                }

                EntityDefinition &def = JsonLoader::getInstance().definitions_[id];

                const auto &components = JsonUtil::JsonAt(it, "components", " object for definition of `" + id + "`");

                for (const auto &component : *components) {
                    def.addComponent(component);
                }
            }
        }

        /**
         * Create a new entity and load its components from json
         * 
         * @param entityManager entity manager to use to create a new entity
         * @param json json object describing the entity to create
         * 
         * @throw
         * 
         * @returns the newly created and loaded entity
         */
        static std::shared_ptr<Entity> createEntity(EntityManager &entityManager, const nlohmann::json &json)
        {
            std::shared_ptr<Entity> entity = entityManager.createEntity();
            const auto &baseJson = json.find("base");
            EntityDefinition builder;

            if (baseJson != json.end()) {
                builder = JsonLoader::getInstance().getDefinition_(baseJson->get<std::string>())->second;
            }

            const auto &components = json.find("components");
            if (components != json.end()) {
                builder.mergeComponents(*components);
            }

            for (const auto &it : builder.components) {
                const auto &factory = JsonLoader::getInstance().factories_.find(it.first);

                if (factory == JsonLoader::getInstance().factories_.cend()) {
                    throw Exception("no factory defined for `" + it.first + "` component");
                }

                JsonLoader::getInstance().factories_[it.first](entity, it.second);
            }
            return entity;
        }

        /**
         * Create a new scene and load its entities from file
         * 
         * @param game game to create the scene into
         * @param file path to the file to load the scene's entities from
         * 
         * @throw
         * 
         * @returns the newly created and loaded scene
         */
        static std::shared_ptr<Scene> createScene(AGame &game, const std::string &file)
        {
            nlohmann::json json = JsonUtil::loadFile(file);

            if (json == nlohmann::json::value_t::discarded) {
                throw Exception("parsing error");
            }

            std::size_t layer = JsonUtil::JsonAt(json, "layer")->get<std::size_t>();
            std::shared_ptr scene = game.createScene(layer);

            JsonLoader::getInstance().loadState_(*scene, json);

            const auto &entities = JsonUtil::JsonAt(json, "entities");
            for (const auto &it : *entities) {
                JsonLoader::createEntity(scene->getEntityManager(), it);
            }
            return scene;
        }

        /**
         * Create a new scene and load its entities from file
         * 
         * @param sceneManager scene manager to use to create a new scene
         * @param file path to the file to load the scene's entities from
         * 
         * @throw
         * 
         * @returns the newly created and loaded scene
         */
        static std::shared_ptr<Scene> createScene(SceneManager &sceneManager, const std::string &file)
        {
            nlohmann::json json = JsonUtil::loadFile(file);

            if (json == nlohmann::json::value_t::discarded) {
                throw Exception("parsing error");
            }

            std::size_t layer = JsonUtil::JsonAt(json, "layer")->get<std::size_t>();
            std::shared_ptr scene = sceneManager.createScene(layer);

            JsonLoader::getInstance().loadState_(*scene, json);

            const auto &entities = JsonUtil::JsonAt(json, "entities");
            for (const auto &it : *entities) {
                JsonLoader::createEntity(scene->getEntityManager(), it);
            }
            return scene;
        }
    };
}