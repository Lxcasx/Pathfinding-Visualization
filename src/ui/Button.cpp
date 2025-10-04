//
// Created by lucas on 10.09.25.
//

#include "Button.h"
#include <iostream>

namespace ui
{
    // Constructor for texture-based button
    Button::Button(const sf::Texture& texture, const sf::Vector2f& position)
        : _position(position)
        , _currentState(ButtonState::Normal)
        , _enabled(true)
        , _isTextBased(false)
        , _normalColor(sf::Color::White)
        , _hoveredColor(sf::Color(220, 220, 220))
        , _pressedColor(sf::Color(180, 180, 180))
        , _disabledColor(sf::Color(100, 100, 100))
        , _onClickCallback(nullptr)
    {
        _sprite = sf::Sprite(texture);
        _sprite->setPosition(_position);
        _size = sf::Vector2f(texture.getSize().x, texture.getSize().y);
    }

    // Constructor for text-based button
    Button::Button(const sf::Font& font, const std::string& text, const sf::Vector2f& position, 
                   const sf::Vector2f& size)
        : _position(position)
        , _size(size)
        , _currentState(ButtonState::Normal)
        , _enabled(true)
        , _isTextBased(true)
        , _normalColor(sf::Color(70, 70, 70))
        , _hoveredColor(sf::Color(90, 90, 90))
        , _pressedColor(sf::Color(50, 50, 50))
        , _disabledColor(sf::Color(40, 40, 40))
        , _normalTextColor(sf::Color::White)
        , _hoveredTextColor(sf::Color::White)
        , _pressedTextColor(sf::Color(200, 200, 200))
        , _disabledTextColor(sf::Color(120, 120, 120))
        , _onClickCallback(nullptr)
    {
        _font = std::cref(font);
        
        // Setup background rectangle
        _background = sf::RectangleShape(_size);
        _background->setPosition(_position);
        _background->setFillColor(_normalColor);
        
        // Setup text
        _text = sf::Text(font, text, 20);
        _text->setFillColor(_normalTextColor);
        
        centerText();
        updateVisualState();
    }

    void Button::update(const sf::Vector2f& mousePos, bool isMousePressed, bool isMouseReleased)
    {
        if (!_enabled)
        {
            _currentState = ButtonState::Disabled;
            updateVisualState();
            return;
        }

        bool isMouseOver = contains(mousePos);
        
        if (isMouseOver)
        {
            if (isMousePressed)
            {
                _currentState = ButtonState::Pressed;
            }
            else if (_currentState == ButtonState::Pressed && isMouseReleased)
            {
                // Button was clicked
                if (_onClickCallback)
                {
                    _onClickCallback();
                }
                _currentState = ButtonState::Hovered;
            }
            else if (_currentState != ButtonState::Pressed)
            {
                _currentState = ButtonState::Hovered;
            }
        }
        else
        {
            _currentState = ButtonState::Normal;
        }

        updateVisualState();
    }

    void Button::draw(sf::RenderWindow& window)
    {
        if (_isTextBased)
        {
            if (_background.has_value())
                window.draw(_background.value());
            if (_text.has_value())
                window.draw(_text.value());
        }
        else
        {
            if (_sprite.has_value())
                window.draw(_sprite.value());
        }
    }

    void Button::setOnClickCallback(std::function<void()> callback)
    {
        _onClickCallback = callback;
    }

    void Button::setPosition(const sf::Vector2f& position)
    {
        _position = position;
        
        if (_isTextBased)
        {
            if (_background.has_value())
                _background->setPosition(_position);
            centerText();
        }
        else
        {
            if (_sprite.has_value())
                _sprite->setPosition(_position);
        }
    }

    sf::Vector2f Button::getPosition() const
    {
        return _position;
    }

    void Button::setSize(const sf::Vector2f& size)
    {
        if (_isTextBased)
        {
            _size = size;
            if (_background.has_value())
                _background->setSize(_size);
            centerText();
        }
    }

    sf::FloatRect Button::getBounds() const
    {
        if (_isTextBased)
        {
            if (_background.has_value())
                return _background->getGlobalBounds();
        }
        else
        {
            if (_sprite.has_value())
                return _sprite->getGlobalBounds();
        }
        return sf::FloatRect(_position, _size);
    }

    void Button::setEnabled(bool enabled)
    {
        _enabled = enabled;
        if (!_enabled)
        {
            _currentState = ButtonState::Disabled;
            updateVisualState();
        }
    }

    bool Button::isEnabled() const
    {
        return _enabled;
    }

    void Button::setText(const std::string& text)
    {
        if (_isTextBased && _text.has_value())
        {
            _text->setString(text);
            centerText();
        }
    }

    void Button::setColors(const sf::Color& normal, const sf::Color& hovered, 
                          const sf::Color& pressed, const sf::Color& disabled)
    {
        _normalColor = normal;
        _hoveredColor = hovered;
        _pressedColor = pressed;
        _disabledColor = disabled;
        updateVisualState();
    }

    void Button::setTextColors(const sf::Color& normal, const sf::Color& hovered, 
                              const sf::Color& pressed, const sf::Color& disabled)
    {
        _normalTextColor = normal;
        _hoveredTextColor = hovered;
        _pressedTextColor = pressed;
        _disabledTextColor = disabled;
        updateVisualState();
    }

    bool Button::contains(const sf::Vector2f& point) const
    {
        return getBounds().contains(point);
    }

    void Button::updateVisualState()
    {
        if (_isTextBased)
        {
            sf::Color bgColor, textColor;
            
            switch (_currentState)
            {
                case ButtonState::Normal:
                    bgColor = _normalColor;
                    textColor = _normalTextColor;
                    break;
                case ButtonState::Hovered:
                    bgColor = _hoveredColor;
                    textColor = _hoveredTextColor;
                    break;
                case ButtonState::Pressed:
                    bgColor = _pressedColor;
                    textColor = _pressedTextColor;
                    break;
                case ButtonState::Disabled:
                    bgColor = _disabledColor;
                    textColor = _disabledTextColor;
                    break;
            }
            
            if (_background.has_value())
                _background->setFillColor(bgColor);
            if (_text.has_value())
                _text->setFillColor(textColor);
        }
        else
        {
            sf::Color spriteColor;
            
            switch (_currentState)
            {
                case ButtonState::Normal:
                    spriteColor = _normalColor;
                    break;
                case ButtonState::Hovered:
                    spriteColor = _hoveredColor;
                    break;
                case ButtonState::Pressed:
                    spriteColor = _pressedColor;
                    break;
                case ButtonState::Disabled:
                    spriteColor = _disabledColor;
                    break;
            }
            
            if (_sprite.has_value())
                _sprite->setColor(spriteColor);
        }
    }

    void Button::centerText()
    {
        if (_isTextBased && _text.has_value())
        {
            sf::FloatRect textBounds = _text->getLocalBounds();
            sf::Vector2f textPosition;
            
            textPosition.x = _position.x + (_size.x - textBounds.size.x) / 2.0f - textBounds.position.x;
            textPosition.y = _position.y + (_size.y - textBounds.size.y) / 2.0f - textBounds.position.y;
            
            _text->setPosition(textPosition);
        }
    }
}
