//
// Created by lucas on 27.01.24.
//

#include "InputManager.h"

namespace engine
{
    bool InputManager::isSpriteClicked(const sf::Sprite &object, sf::Mouse::Button button, sf::RenderWindow &window)
    {
        if (sf::Mouse::isButtonPressed(button))
        {
            return isSpriteFloating(object, window);
        }

        return false;
    }

    bool InputManager::isSpriteFloating(const sf::Sprite &object, sf::RenderWindow &window)
    {
        sf::IntRect tempRect(sf::Vector2i(object.getPosition().x, object.getPosition().y), 
                             sf::Vector2i(object.getGlobalBounds().size.x, object.getGlobalBounds().size.y));

        if (tempRect.contains(sf::Mouse::getPosition(window)))
        {
            return true;
        }

        return false;
    }

    sf::Vector2i InputManager::getMousePosition(sf::RenderWindow &window)
    {
        return sf::Mouse::getPosition(window);
    }
}