//
// Created by lucas on 27.01.24.
//

#ifndef PATHFINDING_ASSETMANAGER_H
#define PATHFINDING_ASSETMANAGER_H

#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace engine {
    class AssetManager {
    public:
        AssetManager() = default;

        ~AssetManager() = default;

        void loadTexture(const std::string &name, const std::string &fileName);

        sf::Texture &getTexture(const std::string &name);

        void loadFont(const std::string &name, const std::string &fileName);

        sf::Font &getFont(const std::string &name);

        void loadSoundBuffer(const std::string &name, const std::string &fileName);

        sf::SoundBuffer &getSoundBuffer(const std::string &name);

    private:
        std::map<std::string, sf::Texture> _textures;
        std::map<std::string, sf::Font> _fonts;
        std::map<std::string, sf::SoundBuffer> _sounds;
    };
}


#endif //PATHFINDING_ASSETMANAGER_H
