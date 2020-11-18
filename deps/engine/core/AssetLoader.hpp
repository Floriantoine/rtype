/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Asset Loader class
*/

#pragma once

#include "../../utils/Exception.hpp"
#include "../../utils/Singleton.hpp"
#include "SFML/Audio/Music.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Texture.hpp"

#include <memory>
#include <unordered_map>

#include <iostream>
    
#define ASSETS_PATH "./client/assets/"

namespace rtype {

    class AssetLoader : public Singleton<AssetLoader> {
      private:
        std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures_;
        std::unordered_map<std::string, std::shared_ptr<sf::Font>> fonts_;
        std::unordered_map<std::string, std::shared_ptr<sf::Music>> audios_;

      public:
        /**
         * AssetLoader Exception class
         */
        class Exception : public rtype::Exception {
          public:
            Exception(const std::string &msg)
                : rtype::Exception("AssetLoader exception: " + msg)
            { }
            Exception(std::string &&msg)
                : rtype::Exception("AssetLoader exception: " + std::move(msg))
            { }
            virtual ~Exception() override = default;
        };

        /**
     * Get a texture from cache or load it from file
     * 
     * @param file texture file name
     * 
     * @throw AssetLoader::Exception if the file could not be parsed
     * 
     * @return the texture object
     */
        static std::shared_ptr<sf::Texture> getTexture(const std::string &file)
        {
            const auto &texture = AssetLoader::getInstance().textures_.find(file);

            if (texture == AssetLoader::getInstance().textures_.cend()) {
                AssetLoader::getInstance().textures_[file] = std::make_shared<sf::Texture>();

                if (AssetLoader::getInstance().textures_[file]->loadFromFile(ASSETS_PATH + file))
                    return AssetLoader::getInstance().textures_[file];
                throw AssetLoader::Exception("Incorrect file path");
            }
            return texture->second;
        }

        /**
     * Get a font from cache or load it from file
     * 
     * @param file font file name
     * 
     * @throw AssetLoader::Exception if the file could not be parsed
     * 
     * @return the font object
     */
        static std::shared_ptr<sf::Font> getFont(const std::string &file)
        {
            const auto &font = AssetLoader::getInstance().fonts_.find(file);

            if (font == AssetLoader::getInstance().fonts_.cend()) {
                AssetLoader::getInstance().fonts_[file] = std::make_shared<sf::Font>();

                if (AssetLoader::getInstance().fonts_[file]->loadFromFile(ASSETS_PATH + file))
                    return AssetLoader::getInstance().fonts_[file];
                throw AssetLoader::Exception("Incorrect file path");
            }
            return font->second;
        }

        /**
     * Get a music from cache or load it from file
     * 
     * @param file music file name
     * 
     * @throw AssetLoader::Exception if the file could not be parsed
     * 
     * @return the music object
     */
        static std::shared_ptr<sf::Music> getSound(const std::string &file)
        {
            const auto &music = AssetLoader::getInstance().audios_.find(file);

            if (music == AssetLoader::getInstance().audios_.cend()) {
                AssetLoader::getInstance().audios_[file] = std::make_shared<sf::Music>();

                if (AssetLoader::getInstance().audios_[file]->openFromFile(ASSETS_PATH + file))
                    return AssetLoader::getInstance().audios_[file];
                throw AssetLoader::Exception("Incorrect file path");
            }
            return music->second;
        }
    };

}