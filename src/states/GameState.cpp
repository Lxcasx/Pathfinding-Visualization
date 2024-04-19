//
// Created by lucas on 29.01.24.
//

#include "GameState.h"

#include <utility>
#include "../DEFINITIONS.h"
#include "plog/Log.h"

GameState::GameState(GameDataRef data) : _data(std::move(data))
{
    PLOGI << "Initializing game state";

    _surface.init(WINDOW_WIDTH, WINDOW_HEIGHT);
}

void GameState::init()
{
}

void GameState::handleInput()
{
    sf::Event event{};

    while (_data->window.pollEvent(event))
    {
        if (sf::Event::Closed == event.type)
        {
            _data->window.close();
        }

        _surface.handleInput();
    }
}

void GameState::update(float dt)
{
    _surface.update(dt);
}

void GameState::draw(float dt)
{
    _data->window.clear(sf::Color::Red);

    _surface.draw(dt);

    _data->window.display();
}

void GameState::loadAssets()
{
}

void GameState::initSprites()
{
}