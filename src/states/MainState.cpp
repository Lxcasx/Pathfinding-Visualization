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
}

void MainState::handleInput()
{
    while (auto event = _data->window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            _data->window.close();
        }

        // hover effect for start button
        if (_startButton && _data->input.isSpriteFloating(*_startButton, _data->window))
        {
            _startButton->setColor(sf::Color(255, 255, 255, 150));
        }
        else if (_startButton)
        {
            _startButton->setColor(sf::Color(255, 255, 255, 255));
        }

        // hover effect for info button
        if (_infoButton && _data->input.isSpriteFloating(*_infoButton, _data->window))
        {
            _infoButton->setColor(sf::Color(255, 255, 255, 150));
        }
        else if (_infoButton)
        {
            _infoButton->setColor(sf::Color(255, 255, 255, 255));
        }

        if (_startButton && _data->input.isSpriteClicked(*_startButton, sf::Mouse::Button::Left, _data->window))
        {
            _data->machine.addState(engine::StateRef(new GameState(_data)), true);
        }
    }
}

void MainState::update(float dt)
{
}

void MainState::draw(float dt)
{
    _data->window.clear(sf::Color::Red);

    if (_background)
        _data->window.draw(*_background);
    if (_startButton)
        _data->window.draw(*_startButton);
    if (_infoButton)
        _data->window.draw(*_infoButton);

    _data->window.display();
}

void MainState::loadAssets()
{
    PLOGI << "Loading assets";
    _data->assets.loadTexture("main_background", MAIN_STATE_BACKGROUND_FILEPATH);
    _data->assets.loadTexture("main_start_button", MAIN_STATE_START_BUTTON_FILEPATH);
    _data->assets.loadTexture("main_info_button", MAIN_STATE_INFO_BUTTON_FILEPATH);
}

void MainState::initSprites()
{
    PLOGI << "Initializing sprites";

    _background = sf::Sprite(_data->assets.getTexture("main_background"));
    _startButton = sf::Sprite(_data->assets.getTexture("main_start_button"));
    _infoButton = sf::Sprite(_data->assets.getTexture("main_info_button"));

    // scale the background to the window size
    float scaleX = (float)_data->window.getSize().x / _background->getTexture().getSize().x;
    float scaleY = (float)_data->window.getSize().y / _background->getTexture().getSize().y;
    _background->setScale(sf::Vector2f(scaleX, scaleY));

    int btnX = (WINDOW_WIDTH / 2) - (_startButton->getGlobalBounds().size.x / 2);
    int btnY = (WINDOW_HEIGHT / 1.8f) - (_startButton->getGlobalBounds().size.y / 2);
    _startButton->setPosition(sf::Vector2f(btnX, btnY));

    btnX = (WINDOW_WIDTH / 2) - (_infoButton->getGlobalBounds().size.x / 2);
    btnY = (WINDOW_HEIGHT / 1.35f) - (_infoButton->getGlobalBounds().size.y / 2);
    _infoButton->setPosition(sf::Vector2f(btnX, btnY));
}