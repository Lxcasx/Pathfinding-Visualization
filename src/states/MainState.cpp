//
// Created by lucas on 29.01.24.
//

#include "MainState.h"

#include <utility>
#include "../DEFINITIONS.h"
#include "GameState.h"
#include "plog/Log.h"

MainState::MainState(GameDataRef data) : _data(std::move(data)) {
}

void MainState::init() {
    PLOGI << "Initializing main state";

    this->_data->assets.loadTexture("main_background", MAIN_STATE_BACKGROUND_FILEPATH);
    this->_data->assets.loadTexture("main_start_button", MAIN_STATE_START_BUTTON_FILEPATH);
    this->_data->assets.loadTexture("main_info_button", MAIN_STATE_INFO_BUTTON_FILEPATH);

    _background.setTexture(this->_data->assets.getTexture("main_background"));
    _startButton.setTexture(this->_data->assets.getTexture("main_start_button"));
    _infoButton.setTexture(this->_data->assets.getTexture("main_info_button"));

    int btnX = (WINDOW_WIDTH / 2) - (_startButton.getGlobalBounds().width / 2);
    int btnY = (WINDOW_HEIGHT / 1.8f) - (_startButton.getGlobalBounds().height / 2);
    _startButton.setPosition(btnX, btnY);

    btnX = (WINDOW_WIDTH / 2) - (_infoButton.getGlobalBounds().width / 2);
    btnY = (WINDOW_HEIGHT / 1.35f) - (_infoButton.getGlobalBounds().height / 2);
    _infoButton.setPosition(btnX, btnY);
}

void MainState::handleInput() {
    sf::Event event{};

    while (this->_data->window.pollEvent(event)) {
        if (sf::Event::Closed == event.type) {
            this->_data->window.close();
        }

        // hover effect for start button
        if (this->_data->input.isSpriteHoverd(this->_startButton, this->_data->window)) {
            this->_startButton.setColor(sf::Color(255, 255, 255, 150));
        } else {
            this->_startButton.setColor(sf::Color(255, 255, 255, 255));
        }

        // hover effect for info button
        if (this->_data->input.isSpriteHoverd(this->_infoButton, this->_data->window)) {
            this->_infoButton.setColor(sf::Color(255, 255, 255, 150));
        } else {
            this->_infoButton.setColor(sf::Color(255, 255, 255, 255));
        }

        if (this->_data->input.isSpriteClicked(this->_startButton, sf::Mouse::Left, this->_data->window)) {
            this->_data->machine.addState(engine::StateRef(new GameState(_data)), true);
        }
    }
}

void MainState::update(float dt) {
}

void MainState::draw(float dt) {
    this->_data->window.clear(sf::Color::Red);

    this->_data->window.draw(this->_background);
    this->_data->window.draw(this->_startButton);
    this->_data->window.draw(this->_infoButton);

    this->_data->window.display();
}