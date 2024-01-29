//
// Created by lucas on 27.01.24.
//

#include "InputManager.h"

namespace engine {
    bool InputManager::isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window) {
        if (sf::Mouse::isButtonPressed(button)) {
            return this->isSpriteHoverd(object, window);
        }

        return false;
    }

    bool InputManager::isSpriteHoverd(sf::Sprite object, sf::RenderWindow &window) {
        sf::IntRect tempRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width,
                             object.getGlobalBounds().height);

        if (tempRect.contains(sf::Mouse::getPosition(window))) {
            return true;
        }

        return false;
    }

    sf::Vector2i InputManager::getMousePosition(sf::RenderWindow &window) {
        return sf::Mouse::getPosition(window);
    }
}