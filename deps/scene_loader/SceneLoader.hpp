/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** SceneLoader
*/

#pragma once

#include "engine/core/ecs/component/ComponentBase.hpp"
#include "engine/core/scene/Scene.hpp"
#include "nlohmann/json.hpp"
#include "utils/Exception.hpp"

#include <fstream>
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

namespace rtype {
    class SceneLoader {
      public:
        typedef std::function<std::unique_ptr<ComponentBase>(const nlohmann::json &body)> component_factory_t;

        class Exception : public rtype::Exception {
          public:
            Exception(const std::string &msg)
                : rtype::Exception("SceneLoader exception: " + msg)
            { }
            Exception(std::string &&msg)
                : rtype::Exception("SceneLoader exception: " + std::move(msg))
            { }
            virtual ~Exception() override = default;
        };

      private:
        struct EntityDefinition {
            std::unordered_map<std::string, nlohmann::json> components;

            EntityDefinition &operator=(const EntityDefinition &other)
            {
                this->components = other.components;
                return *this;
            }
        };

        static std::unordered_map<std::string, component_factory_t> componentFactory_;

        bool good_ { true };
        nlohmann::json json_;
        std::unordered_map<std::string, EntityDefinition> definitions_;

        static const auto jsonAt_(const nlohmann::json &json, const std::string &key, const std::string &errorContext = "")
        {
            const auto &value = json.find(key);
            if (value == json.end())
                throw Exception("expected `" + key + "` " + errorContext);
            return value;
        }

        void addComponent_(EntityDefinition &def, const nlohmann::json &body)
        {
            const auto &typeJson = this->jsonAt_(body, "type", "for an object of type `component`");
            const std::string &type = typeJson->get<std::string>();

            def.components[typeJson->get<std::string>()] = body;
        }

        const auto getDefinition_(const std::string &key, bool throwOnError = true) const
        {
            const auto def = this->definitions_.find(key);
            if (throwOnError && def == this->definitions_.end())
                throw Exception("no defintion found for " + key);
            return (def);
        }

        void loadState_(Scene &scene) const
        {
            static const std::unordered_map<std::string, Scene::State> states = {
                { "INACTIVE", Scene::STATE_INACTIVE },
                { "RUNNING", Scene::STATE_RUNNING },
                { "PAUSED", Scene::STATE_PAUSED }
            };

            const auto &stateJson = this->jsonAt_(this->json_, "state");
            const auto &stateStr = stateJson->get<std::string>();
            const auto &state = states.find(stateStr);

            if (state == states.cend()) {
                throw Exception("value `" + stateStr + "` for `state` isn't valid");
            }
            scene.setState(state->second);
        }

        void loadDefinitions_()
        {
            static bool loaded = false;

            if (loaded)
                return;
            loaded = true;

            auto defs = this->json_.find("definitions");
            for (const auto &it : *defs) {
                const auto &id = this->jsonAt_(it, "id", "for an object of type `definition`")->get<std::string>();
                const auto &check = this->getDefinition_(id, false);
                if (check != this->definitions_.cend()) {
                    throw Exception("multiple definition of `" + id + "`");
                }

                EntityDefinition &def = this->definitions_[id];

                const auto &components = this->jsonAt_(it, "components", " object for definition of `" + id + "`");

                for (const auto &component : *components) {
                    addComponent_(def, component);
                }
            }
        }

        void loadComponents_(EntityDefinition &entity, const nlohmann::json &json) const
        {
            for (const auto &component : json) {
                std::string type = this->jsonAt_(json, "type")->get<std::string>();
                entity.components[type].merge_patch(json);
            }
        }

        void loadEntity_(Scene &scene, const nlohmann::json &json) const
        {
            const auto &baseJson = json.find("base");
            EntityDefinition builder;

            if (baseJson != json.end()) {
                builder = this->getDefinition_(baseJson->get<std::string>())->second;
            }

            const auto &components = json.find("components");
            if (components != json.end()) {
                this->loadComponents_(builder, *components);
            }

            std::shared_ptr<Entity> entity = scene.createEntity().lock();
            for (const auto &it : builder.components) {
                const auto &factory = SceneLoader::componentFactory_.find(it.first);

                if (factory == SceneLoader::componentFactory_.cend()) {
                    throw Exception("no factory defined for `" + it.first + "` component");
                }
                // entity.addComponent { this->componentFactory_[it.first](it.second) };
            }
        }

      public:
        ~SceneLoader() = default;

        SceneLoader(const std::string &file)
        {
            std::ifstream fd(file);

            this->good_ = fd.good();
            if (!this->good_) {
                return;
            }
            this->json_ = nlohmann::json::parse(fd, nullptr, false, true);
            if (this->json_ == nlohmann::json::value_t::discarded) {
                this->good_ = false;
            }
        }

        static void addComponentFactory(const std::string &type, component_factory_t factory)
        {
            SceneLoader::componentFactory_[type] = factory;
        }

        std::unique_ptr<Scene> load()
        {
            if (!this->good_)
                throw Exception("parsing error");

            std::unique_ptr scenePtr = std::make_unique<Scene>();

            this->loadDefinitions_();
            this->loadState_(*scenePtr);

            const auto &json = this->jsonAt_(this->json_, "entities");

            for (const auto &it : *json) {
                this->loadEntity_(*scenePtr, it);
            }
            return scenePtr;
        }
    };
}
