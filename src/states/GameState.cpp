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

    _surface.init(WINDOW_WIDTH, WINDOW_HEIGHT, GRID_SIZE);
}

void GameState::init()
{
}

void GameState::handleInput()
{
    sf::Event event{};

    while (this->_data->window.pollEvent(event))
    {
        if (sf::Event::Closed == event.type)
        {
            this->_data->window.close();
        }

        this->_surface.handleInput();
    }
}

void GameState::update(float dt)
{
    this->_surface.update(dt);
}

void GameState::draw(float dt)
{
    this->_data->window.clear(sf::Color::Red);

    this->_surface.draw(dt);

    this->_data->window.display();
}

void GameState::loadAssets()
{
}

void GameState::initSprites()
{
}