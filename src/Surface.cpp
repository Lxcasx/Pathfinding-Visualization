//
// Created by lucas on 29.01.24.
//

#include "Surface.h"
#include "plog/Log.h"
#include "DEFINITIONS.h"
#include <cmath>
#include <chrono>
#include <utility>

Surface::Surface(GameDataRef data) : _data(std::move(data)), _path(grid) {
}

void Surface::prepare() {
    for (int i = 0; i < this->rows; i++) {
        std::vector<CellField> row;

        for (int j = 0; j < this->cols; j++) {
            if (j == 0 || j == this->cols - 1 || i == 0 || i == this->rows - 1)
                row.push_back(CellField{CellState::WALL});
            else
                row.push_back(CellField{CellState::EMPTY});
        }

        grid->push_back(row);
    }

    level.resize(width * height);
    map.load(sf::Vector2u(GRID_SIZE, GRID_SIZE), width, height);
}

void Surface::init(int width, int height, float size) {
    this->width = width;
    this->height = height;
    this->rows = std::round(width / size);
    this->cols = std::round(height / size);
    this->size = size;

    this->prepare();
}

void Surface::setPosition(float x, float y) {
}

void Surface::draw(float dt) {
    _data->window.draw(map);

    if (this->startPos != Cell{-1, -1} && this->endPos != Cell{-1, -1} && !_path.isFinished) {
        //_path.nextStep();
        //map.update(grid);
    }

    if (this->startPos != Cell{-1, -1} && this->endPos != Cell{-1, -1} && this->_path.isFinished) {
        //this->_path.constructPath();
        //map.update(grid);
    }
}

void Surface::update(float dt) {

}

void Surface::setWall(sf::Vector2i pos) {
    map.setWall(pos);
}


void Surface::handleInput() {
    // draw wall
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        this->setWall(sf::Mouse::getPosition(this->_data->window));
    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        this->setStart(sf::Mouse::getPosition(this->_data->window));
    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        this->setEnd(sf::Mouse::getPosition(this->_data->window));
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
        this->clear();
    } else {
        lastPos = Cell{-1, -1};
    }
}

void Surface::clear() {
    this->grid->clear();
    this->prepare();
    this->_path.clear();
    this->startPos = Cell{-1, -1};
    this->endPos = Cell{-1, -1};
    map.update();
}

void Surface::setStart(sf::Vector2i pos) {
}

void Surface::setStart(Cell cell) {
}

void Surface::setEnd(sf::Vector2i pos) {

}

void Surface::setEnd(Cell cell) {
}

void Surface::save() {
}