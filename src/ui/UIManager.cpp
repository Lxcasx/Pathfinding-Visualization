//
// Created by lucas on 10.09.25.
//

#include "UIManager.h"
#include <algorithm>

namespace ui
{
    void UIManager::addButton(std::shared_ptr<Button> button)
    {
        if (button)
        {
            _buttons.push_back(button);
        }
    }

    void UIManager::removeButton(std::shared_ptr<Button> button)
    {
        _buttons.erase(
            std::remove(_buttons.begin(), _buttons.end(), button),
            _buttons.end()
        );
    }

    void UIManager::clear()
    {
        _buttons.clear();
    }

    void UIManager::update(const sf::RenderWindow& window)
    {
        sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePos = window.mapPixelToCoords(mousePixelPos);
        
        bool isMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        static bool wasMousePressed = false;
        bool isMouseReleased = wasMousePressed && !isMousePressed;
        
        handleMouseInput(mousePos, isMousePressed, isMouseReleased);
        
        wasMousePressed = isMousePressed;
    }

    void UIManager::draw(sf::RenderWindow& window)
    {
        for (auto& button : _buttons)
        {
            if (button)
            {
                button->draw(window);
            }
        }
    }

    void UIManager::handleMouseInput(const sf::Vector2f& mousePos, bool isMousePressed, bool isMouseReleased)
    {
        for (auto& button : _buttons)
        {
            if (button)
            {
                button->update(mousePos, isMousePressed, isMouseReleased);
            }
        }
    }

    const std::vector<std::shared_ptr<Button>>& UIManager::getButtons() const
    {
        return _buttons;
    }
}
