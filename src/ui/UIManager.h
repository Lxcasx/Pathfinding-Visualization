//
// Created by lucas on 10.09.25.
//

#ifndef PATHFINDING_UIMANAGER_H
#define PATHFINDING_UIMANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Button.h"

namespace ui
{
    class UIManager
    {
    public:
        UIManager() = default;
        ~UIManager() = default;

        // Add a button to the UI manager
        void addButton(std::shared_ptr<Button> button);

        // Remove a button from the UI manager
        void removeButton(std::shared_ptr<Button> button);

        // Clear all buttons
        void clear();

        // Update all UI elements
        void update(const sf::RenderWindow& window);

        // Draw all UI elements
        void draw(sf::RenderWindow& window);

        // Handle mouse input for all UI elements
        void handleMouseInput(const sf::Vector2f& mousePos, bool isMousePressed, bool isMouseReleased);

        // Get all buttons
        const std::vector<std::shared_ptr<Button>>& getButtons() const;

    private:
        std::vector<std::shared_ptr<Button>> _buttons;
    };
}

#endif // PATHFINDING_UIMANAGER_H
