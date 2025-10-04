//
// Created by lucas on 10.09.25.
//

#ifndef PATHFINDING_BUTTON_H
#define PATHFINDING_BUTTON_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include <optional>

namespace ui
{
    enum class ButtonState
    {
        Normal,
        Hovered,
        Pressed,
        Disabled
    };

    class Button
    {
    public:
        // Constructor for texture-based button
        Button(const sf::Texture& texture, const sf::Vector2f& position);
        
        // Constructor for text-based button
        Button(const sf::Font& font, const std::string& text, const sf::Vector2f& position, 
               const sf::Vector2f& size = sf::Vector2f(200, 50));

        // Destructor
        ~Button() = default;

        // Update button state based on mouse input
        void update(const sf::Vector2f& mousePos, bool isMousePressed, bool isMouseReleased);

        // Render the button
        void draw(sf::RenderWindow& window);

        // Set callback function to be called when button is clicked
        void setOnClickCallback(std::function<void()> callback);

        // Set button position
        void setPosition(const sf::Vector2f& position);
        
        // Get button position
        sf::Vector2f getPosition() const;

        // Set button size (only for text-based buttons)
        void setSize(const sf::Vector2f& size);

        // Get button bounds
        sf::FloatRect getBounds() const;

        // Enable/disable the button
        void setEnabled(bool enabled);
        bool isEnabled() const;

        // Set text (only for text-based buttons)
        void setText(const std::string& text);
        
        // Set colors for different states (only for text-based buttons)
        void setColors(const sf::Color& normal, const sf::Color& hovered, 
                      const sf::Color& pressed, const sf::Color& disabled);

        // Set text colors for different states
        void setTextColors(const sf::Color& normal, const sf::Color& hovered, 
                          const sf::Color& pressed, const sf::Color& disabled);

        // Check if point is inside button
        bool contains(const sf::Vector2f& point) const;

    private:
        // Button properties
        sf::Vector2f _position;
        sf::Vector2f _size;
        ButtonState _currentState;
        bool _enabled;
        bool _isTextBased;

        // Texture-based button components
        std::optional<sf::Sprite> _sprite;
        
        // Text-based button components
        std::optional<sf::RectangleShape> _background;
        std::optional<sf::Text> _text;
        std::optional<std::reference_wrapper<const sf::Font>> _font;

        // Colors for different states
        sf::Color _normalColor;
        sf::Color _hoveredColor;
        sf::Color _pressedColor;
        sf::Color _disabledColor;

        // Text colors for different states
        sf::Color _normalTextColor;
        sf::Color _hoveredTextColor;
        sf::Color _pressedTextColor;
        sf::Color _disabledTextColor;

        // Callback function
        std::function<void()> _onClickCallback;

        // Helper methods
        void updateVisualState();
        void centerText();
    };
}

#endif // PATHFINDING_BUTTON_H
