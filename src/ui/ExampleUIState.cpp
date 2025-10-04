//
// Created by lucas on 10.09.25.
//

#include "ExampleUIState.h"
#include "../DEFINITIONS.h"
#include "../states/MainState.h"
#include "plog/Log.h"

ExampleUIState::ExampleUIState(GameDataRef data) : _data(data)
{
}

void ExampleUIState::init()
{
    PLOGI << "Initializing Example UI State";
    
    loadAssets();
    initSprites();
    setupUI();
}

void ExampleUIState::loadAssets()
{
    PLOGI << "Loading assets for Example UI State";
    // We're reusing assets that are already loaded from MainState
    // No additional assets needed for this example
}

void ExampleUIState::initSprites()
{
    PLOGI << "Initializing sprites for Example UI State";
    // No additional sprites needed for this example
}

void ExampleUIState::handleInput()
{
    while (auto event = _data->window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            _data->window.close();
        }
        
        // Go back to main state on Escape key
        if (event->is<sf::Event::KeyPressed>())
        {
            const auto& keyEvent = event->getIf<sf::Event::KeyPressed>();
            if (keyEvent && keyEvent->code == sf::Keyboard::Key::Escape)
            {
                PLOGI << "Escape pressed, going back to main menu";
                _data->machine.addState(engine::StateRef(new MainState(_data)), true);
            }
        }
    }
}

void ExampleUIState::update(float dt)
{
    _uiManager.update(_data->window);
}

void ExampleUIState::draw(float dt)
{
    _data->window.clear(sf::Color(50, 50, 100)); // Different background color to show it's a different state
    
    // Draw UI elements
    _uiManager.draw(_data->window);
    
    _data->window.display();
}

void ExampleUIState::setupUI()
{
    PLOGI << "Setting up UI elements";
    
    // Since we don't have a font loaded, let's create texture-based buttons using existing assets
    // We'll reuse the button textures from the main state
    
    float centerX = WINDOW_WIDTH / 2.0f;
    float startY = 200.0f;
    float buttonSpacing = 80.0f;
    
    // Create buttons using the existing button textures
    try {
        // Back button using the info button texture (reused)
        _exitButton = std::make_shared<ui::Button>(
            _data->assets.getTexture("main_info_button"),
            sf::Vector2f(centerX - 100, startY)
        );
        _exitButton->setOnClickCallback([this]() { onExitButtonClicked(); });
        _uiManager.addButton(_exitButton);
        
        // Settings button using the start button texture (reused)
        _settingsButton = std::make_shared<ui::Button>(
            _data->assets.getTexture("main_start_button"),
            sf::Vector2f(centerX - 100, startY + buttonSpacing)
        );
        _settingsButton->setOnClickCallback([this]() { onSettingsButtonClicked(); });
        _uiManager.addButton(_settingsButton);
        
        // Start button using the start button texture 
        _startButton = std::make_shared<ui::Button>(
            _data->assets.getTexture("main_start_button"),
            sf::Vector2f(centerX - 100, startY + buttonSpacing * 2)
        );
        _startButton->setOnClickCallback([this]() { onStartButtonClicked(); });
        _uiManager.addButton(_startButton);
        
        PLOGI << "UI setup completed successfully";
    }
    catch (const std::exception& e) {
        PLOGI << "Error setting up UI: " << e.what();
    }
}

void ExampleUIState::onStartButtonClicked()
{
    PLOGI << "Start button clicked!";
    // Add your start game logic here
    // For example: _data->machine.addState(engine::StateRef(new GameState(_data)), true);
}

void ExampleUIState::onExitButtonClicked()
{
    PLOGI << "Exit button clicked! Going back to main menu";
    // Go back to the main state instead of closing the window
    _data->machine.addState(engine::StateRef(new MainState(_data)), true);
}

void ExampleUIState::onSettingsButtonClicked()
{
    PLOGI << "Settings button clicked!";
    // Add your settings logic here
    // For example: _data->machine.addState(engine::StateRef(new SettingsState(_data)), true);
}
