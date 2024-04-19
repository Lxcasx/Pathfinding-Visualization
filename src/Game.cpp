//
// Created by lucas on 27.01.24.
//

#include "Game.h"
#include "plog/Log.h"
#include "states/SplashState.h"
#include "engine/StateMachine.h"

Game::Game(int width, int height, const std::string &title)
{
    PLOGI << "Initializing the game.";

    _data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
    _data->window.setFramerateLimit(120);
    _data->machine.addState(engine::StateRef(new SplashState(this->_data)));

    this->run();
}

void Game::run()
{
    float newTime, frameTime, interpolation;

    float currentTime = this->_clock.getElapsedTime().asSeconds();
    float accumulator = 0.0f;

    while (this->_data->window.isOpen())
    {
        this->_data->machine.processStateChanges();

        newTime = this->_clock.getElapsedTime().asSeconds();
        frameTime = newTime - currentTime;

        if (frameTime > 0.25f)
        {
            frameTime = 0.25f;
        }

        currentTime = newTime;
        accumulator += frameTime;

        while (accumulator >= dt)
        {
            this->_data->machine.getActiveState()->handleInput();
            this->_data->machine.getActiveState()->update(dt);

            accumulator -= dt;
        }

        interpolation = accumulator / dt;
        this->_data->machine.getActiveState()->draw(interpolation);
    }
}