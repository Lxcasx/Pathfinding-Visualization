//
// Created by lucas on 29.01.24.
//

#include "MainState.h"

#include <utility>
#include "../DEFINITIONS.h"
#include "GameState.h"
#include "plog/Log.h"

MainState::MainState(GameDataRef data) : _data(std::move(data))
{
}

void MainState::init()
{
    PLOGI << "Initializing main state";

    loadAssets();
    initSprites();
    setupUI();
}

void MainState::handleInput()
{
    while (auto event = _data->window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            _data->window.close();
        }
        
        // No need for manual hover/click handling - UI buttons handle this automatically
    }
}

void MainState::update(float dt)
{
    // Update UI components
    _uiManager.update(_data->window);
}

void MainState::draw(float dt)
{
    _data->window.clear(sf::Color::Red);

    if (_background)
        _data->window.draw(*_background);

    // Draw UI components (buttons are now handled by UIManager)
    _uiManager.draw(_data->window);

    _data->window.display();
}

void MainState::loadAssets()
{
    PLOGI << "Loading assets";
    _data->assets.loadTexture("main_background", MAIN_STATE_BACKGROUND_FILEPATH);
    _data->assets.loadFont("ui_font", "./resources/res/fonts/Electrolize-Regular.ttf");
}

void MainState::initSprites()
{
    PLOGI << "Initializing sprites";

    _background = sf::Sprite(_data->assets.getTexture("main_background"));

    // scale the background to the window size
    float scaleX = (float)_data->window.getSize().x / _background->getTexture().getSize().x;
    float scaleY = (float)_data->window.getSize().y / _background->getTexture().getSize().y;
    _background->setScale(sf::Vector2f(scaleX, scaleY));
}

void MainState::setupUI()
{
    PLOGI << "Setting up UI components";
    
    // Get font from asset manager
    sf::Font& font = _data->assets.getFont("ui_font");
    
    // Create Start button in center position (text-based)
    float centerX = WINDOW_WIDTH / 2.0f;
    _startButton = std::make_shared<ui::Button>(
        font,
        "START GAME",
        sf::Vector2f(centerX - 200, WINDOW_HEIGHT / 1.8f - 25),
        sf::Vector2f(400, 50)
    );
    _startButton->setOnClickCallback([this]() {
        PLOGI << "Start button clicked!";
        _data->machine.addState(engine::StateRef(new GameState(_data)), true);
    });
    _startButton->setColors(
        sf::Color(28, 28, 28),   // Normal
        sf::Color(32, 32, 32),  // Hovered
        sf::Color(24, 24, 24),   // Pressed
        sf::Color(100, 100, 100)   // Disabled
    );
    _uiManager.addButton(_startButton);
    
    // Create Info button below start button (text-based)
    _infoButton = std::make_shared<ui::Button>(
        font,
        "INFO",
        sf::Vector2f(centerX - 200, WINDOW_HEIGHT / 1.8f + 50),
        sf::Vector2f(400, 50)
    );
    _infoButton->setOnClickCallback([this]() {
        PLOGI << "Info button clicked!";
        // You can add info functionality here later
    });
    _infoButton->setColors(
        sf::Color(28, 28, 28),   // Normal
        sf::Color(32, 32, 32),  // Hovered
        sf::Color(24, 24, 24),   // Pressed
        sf::Color(100, 100, 100)   // Disabled
    );
    _uiManager.addButton(_infoButton);
    
    // Create Exit button below info button (text-based)
    _exitButton = std::make_shared<ui::Button>(
        font,
        "EXIT",
        sf::Vector2f(centerX - 200, WINDOW_HEIGHT / 1.8f + 125),
        sf::Vector2f(400, 50)
    );
    _exitButton->setOnClickCallback([this]() {
        PLOGI << "Exit button clicked!";
        _data->window.close();
    });
    _exitButton->setColors(
        sf::Color(28, 28, 28),   // Normal
        sf::Color(32, 32, 32),  // Hovered
        sf::Color(24, 24, 24),   // Pressed
        sf::Color(100, 100, 100)   // Disabled
    );
    _uiManager.addButton(_exitButton);
    
    PLOGI << "UI setup completed";
}