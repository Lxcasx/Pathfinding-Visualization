//
// Created by lucas on 27.01.24.
//

#include "SplashState.h"
#include "plog/Log.h"
#include <filesystem>
#include "../DEFINITIONS.h"
#include "MainState.h"

SplashState::SplashState(GameDataRef data) : _data(data)
{
}

void SplashState::init()
{
    PLOGI << "Initializing splash state";

    loadAssets();
    initSprites();
}

void SplashState::handleInput()
{
    sf::Event event;

    while (_data->window.pollEvent(event))
    {
        if (sf::Event::Closed == event.type)
        {
            _data->window.close();
        }
    }
}

void SplashState::update(float dt)
{
    if (_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
    {
        PLOGI << "Go to main menu";
        _data->machine.addState(engine::StateRef(new MainState(_data)), true);
    }
}

void SplashState::draw(float dt)
{
    _data->window.clear(sf::Color::Red);

    _data->window.draw(_background);

    _data->window.display();
}

void SplashState::loadAssets()
{
    PLOGI << "Loading assets";
    _data->assets.loadTexture("splash_background", SPLASH_STATE_BACKGROUND_FILEPATH);
}

void SplashState::initSprites()
{
    PLOGI << "Initializing sprites";
    _background.setTexture(_data->assets.getTexture("splash_background"));

    // scale the background to the window size
    float scaleX = (float)_data->window.getSize().x / _background.getTexture()->getSize().x;
    float scaleY = (float)_data->window.getSize().y / _background.getTexture()->getSize().y;
    _background.setScale(scaleX, scaleY);
}