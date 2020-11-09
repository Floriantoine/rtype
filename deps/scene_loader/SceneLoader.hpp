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
        typedef std::function<std::shared_ptr<ComponentBase>(const nlohmann::json &json, const std::shared_ptr<ComponentBase> &)> component_factory_t;

        class Exception : rtype::Exception {
          public:
            Exception(const std::string &msg)
                : rtype::Exception("SceneLoader exception: " + msg)
            {
            }

            Exception(std::string &&msg)
                : rtype::Exception("SceneLoader exception: " + std::move(msg))
            {
            }
            virtual ~Exception() override = default;
        };

      private:
        static std::unordered_map<std::string, component_factory_t> componentFactory_;

        struct EntityDefinition {
            std::vector<std::shared_ptr<ComponentBase>> components;
        };

        bool good_ { false };
        nlohmann::json json_;
        std::unordered_map<std::string, EntityDefinition> definitions_;
        Scene::State state_;

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
            const auto &factory = SceneLoader::componentFactory_.find(type);

            if (factory == SceneLoader::componentFactory_.cend()) {
                throw Exception("no factory defined for `" + type + "` component");
            }
            def.components.emplace_back(std::move(factory->second(body, nullptr)));
        }

        const auto getDefinition_(const std::string &key, bool throwOnError = true)
        {
            const auto &def = this->definitions_.find(key);
            if (throwOnError && def != this->definitions_.end())
                throw Exception("no defintion found for " + key);
            return (def);
        }

        void loadState_()
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
            this->state_ = state->second;
        }

        void loadDefinitions_()
        {
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
            } else {
                this->loadState_();
                this->loadDefinitions_();
            }
        }

        static void addComponentFactory(const std::string &type, component_factory_t factory)
        {
            SceneLoader::componentFactory_[type] = factory;
        }

        std::unique_ptr<Scene> load() const
        {
            std::unique_ptr scenePtr = std::make_unique<Scene>();

            scenePtr->setState(this->state_);

            const auto &json = this->jsonAt_(this->json_, "entities");

            for (const auto &it : *json) {
                const auto &baseJson = it.find("base");
                if (baseJson != it.end()) {
                    // load template components
                }
                // create entity
                // for each component in json {
                //     call component factory with template if any
                //     add component to entity
                // }
                // /!\ don't forget to add components that are defined only in the template and not in the JSON
                //     (because the previous loop won't take them into account)
            }
            return scenePtr;
        }
    };
}
