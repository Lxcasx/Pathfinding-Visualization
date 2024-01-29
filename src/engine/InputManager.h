//
// Created by lucas on 27.01.24.
//

#ifndef PATHFINDING_INPUTMANAGER_H
#define PATHFINDING_INPUTMANAGER_H

#include <SFML/Graphics.hpp>

namespace engine {
    class InputManager {
    public:
        InputManager() = default;

        ~InputManager() = default;

        bool isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window);

        bool isSpriteHoverd(sf::Sprite object, sf::RenderWindow &window);

        sf::Vector2i getMousePosition(sf::RenderWindow &window);
    };
}

#endif //PATHFINDING_INPUTMANAGER_H
