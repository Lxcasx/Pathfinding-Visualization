//
// Created by lucas on 27.01.24.
//

#include "AssetManager.h"
#include "SFML/Audio.hpp"
#include "plog/Log.h"

namespace engine {
    void AssetManager::loadTexture(const std::string &name, const std::string &fileName) {
        sf::Texture texture;

        if (texture.loadFromFile(fileName)) {
            this->_textures[name] = texture;
        }
    }

    sf::Texture &AssetManager::getTexture(const std::string &name) {
        return this->_textures.at(name);
    }

    void AssetManager::loadFont(const std::string &name, const std::string &fileName) {
        sf::Font font;

        if (font.loadFromFile(fileName)) {
            this->_fonts[name] = font;
        }
    }

    sf::Font &AssetManager::getFont(const std::string &name) {
        return this->_fonts.at(name);
    }

    void AssetManager::loadSoundBuffer(const std::string &name, const std::string &fileName) {
        sf::SoundBuffer sound;

        if (sound.loadFromFile(fileName)) {
            this->_sounds[name] = sound;
        }
    }

    sf::SoundBuffer &AssetManager::getSoundBuffer(const std::string &name) {
        return this->_sounds.at(name);
    }
}