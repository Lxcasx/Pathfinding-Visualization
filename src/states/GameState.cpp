//
// Created by lucas on 29.01.24.
//

#include "GameState.h"

#include <utility>
#include "../DEFINITIONS.h"
#include "plog/Log.h"

GameState::GameState(GameDataRef data) : _data(std::move(data))
{
    _surface.init(WINDOW_WIDTH, WINDOW_HEIGHT);
    
    // Initialize font first
    _font = sf::Font();
    
    // Try to load font with multiple fallbacks
    bool fontLoaded = false;
    
    // Try common font paths across different operating systems
    std::vector<std::string> fontPaths = {
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/TTF/arial.ttf",
        "/System/Library/Fonts/Arial.ttf", // macOS
        "C:/Windows/Fonts/arial.ttf"       // Windows
    };
    
    for (const auto& fontPath : fontPaths) {
        if (_font->openFromFile(fontPath)) {
            fontLoaded = true;
            break;
        }
    }
    
    if (!fontLoaded) {
        // Keep the default font that was created
        PLOGI << "Using default font";
    }
    
    // Setup algorithm text
    _algorithmText = sf::Text(*_font);
    _algorithmText->setCharacterSize(24);
    _algorithmText->setFillColor(sf::Color::White);
    _algorithmText->setPosition(sf::Vector2f(30, 20));
    
    // Setup instructions text
    _instructionsText = sf::Text(*_font);
    _instructionsText->setCharacterSize(16);
    _instructionsText->setFillColor(sf::Color::White);
    _instructionsText->setPosition(sf::Vector2f(30, 50));
    _instructionsText->setString("Controls: Left Click - Start/Wall (+Shift), Right Click - End, C - Clear, SPACE - Switch Algorithm");
    
    updateTexts();
}

void GameState::init()
{
}

void GameState::handleInput()
{
    while (auto event = _data->window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            _data->window.close();
        }
        
        // Handle key press events (not key held)
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code == sf::Keyboard::Key::Space)
            {
                _surface.switchAlgorithm();
            }
            else if (keyPressed->code == sf::Keyboard::Key::C)
            {
                _surface.clear();
            }
        }

        _surface.handleInput();
    }
}

void GameState::update(float dt)
{
    _surface.update(dt);
    updateTexts();
}

void GameState::draw(float dt)
{
    _data->window.clear(sf::Color::Red);

    _surface.draw(dt);
    
    // Draw UI texts
    if (_algorithmText)
        _data->window.draw(*_algorithmText);
    if (_instructionsText)
        _data->window.draw(*_instructionsText);

    _data->window.display();
}

void GameState::loadAssets()
{
}

void GameState::initSprites()
{
}

void GameState::updateTexts()
{
    if (_algorithmText)
        _algorithmText->setString("Algorithm: " + _surface.getCurrentAlgorithmName());
}