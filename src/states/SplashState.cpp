//
// Created by lucas on 27.01.24.
//

#include "SplashState.h"
#include "plog/Log.h"
#include <filesystem>
#include "../DEFINITIONS.h"
#include "MainState.h"


SplashState::SplashState(GameDataRef data) : _data(data) {
}

void SplashState::init() {
    PLOGI << "Initializing splash state";

    this->_data->assets.loadTexture("splash_background", SPLASH_STATE_BACKGROUND_FILEPATH);

    _background.setTexture(this->_data->assets.getTexture("splash_background"));
}

void SplashState::handleInput() {
    sf::Event event;

    while (this->_data->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            this->_data->window.close();
        }
    }
}

void SplashState::update(float dt) {
    if (this->_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME) {
        PLOGI << "Go to main menu";
        this->_data->machine.addState(engine::StateRef(new MainState(_data)), true);
    }
}

void SplashState::draw(float dt) {
    this->_data->window.clear(sf::Color::Red);

    this->_data->window.draw(this->_background);

    this->_data->window.display();
}