//
// Created by lucas on 29.01.24.
//

#include "Surface.h"
#include "DEFINITIONS.h"
#include "pathfinding/BFSFinding.h"
#include <utility>
#include <cmath>

Surface::Surface(GameDataRef data) : _data(std::move(data)), _bfs(&this->grid) {
}

void Surface::prepare() {
    for (int i = 0; i < this->rows; i++) {
        std::vector<Cell> row;

        for (int j = 0; j < this->cols; j++) {
            if (j == 0 || j == this->cols - 1 || i == 0 || i == this->rows - 1)
                row.push_back(Cell{CellState::WALL});
            else
                row.push_back(Cell{CellState::EMPTY});
        }

        grid.push_back(row);
    }
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
    // draw border around grid
    sf::RectangleShape border(sf::Vector2f(width, height));
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineThickness(2);
    border.setOutlineColor(sf::Color::Red);
    this->_data->window.draw(border);

    sf::RectangleShape shape(sf::Vector2f(this->size, this->size));

    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            Cell cell = this->grid[i][j];

            if (cell.state == CellState::EMPTY) {
                if (cell.visited) {
                    shape.setFillColor(COLOR_VISITED);
                } else {
                    shape.setFillColor(COLOR_BG);
                }
            } else if (cell.state == CellState::WALL) {
                shape.setFillColor(COLOR_WALL);
            } else if (cell.state == CellState::START) {
                shape.setFillColor(COLOR_START);
            } else if (cell.state == CellState::END) {
                shape.setFillColor(COLOR_END);
            } else if (cell.state == CellState::PATH) {
                shape.setFillColor(COLOR_PATH);
            }

            int x = i * size;
            int y = j * size;

            shape.setPosition(x, y);
            this->_data->window.draw(shape);
        }
    }

    if (this->startPos != nullptr && this->endPos != nullptr && !_bfs.finished) {
        _bfs.nextStep();
    }

    if (this->startPos != nullptr && this->endPos != nullptr && this->_bfs.finished) {
        std::vector<sf::Vector2i> path = this->_bfs.constructPath();
    }
}

void Surface::setWall(sf::Vector2i pos) {
    int row = pos.x / this->size;
    int col = pos.y / this->size;

    if (row < 0 || col < 0)
        return;
    if (row >= this->rows || col >= this->cols)
        return;

    this->grid[row][col].state = CellState::WALL;
}

void Surface::handleInput() {
    // draw wall
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
        this->setWall(sf::Mouse::getPosition(this->_data->window));
    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        this->setStart(sf::Mouse::getPosition(this->_data->window));
    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        this->setEnd(sf::Mouse::getPosition(this->_data->window));
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
        this->clear();
    }
}

void Surface::clear() {
    this->grid.clear();
    this->prepare();
    this->_bfs.clear();
    this->startPos = nullptr;
    this->endPos = nullptr;
}

void Surface::setStart(sf::Vector2i pos) {
    int row = pos.x / this->size;
    int col = pos.y / this->size;

    if (row < 0 || col < 0)
        return;
    if (row >= this->rows || col >= this->cols)
        return;

    if (this->grid[row][col].state == CellState::WALL || this->grid[row][col].state == CellState::END)
        return;

    if (this->startPos != nullptr)
        this->grid[this->startPos->x][this->startPos->y].state = CellState::EMPTY;

    startPos = new sf::Vector2i(row, col);
    _bfs.setStart(*startPos);
    this->grid[row][col].state = CellState::START;
}

void Surface::setEnd(sf::Vector2i pos) {
    int row = pos.x / this->size;
    int col = pos.y / this->size;

    if (row < 0 || col < 0)
        return;
    if (row >= this->rows || col >= this->cols)
        return;

    if (this->grid[row][col].state == CellState::WALL || this->grid[row][col].state == CellState::START)
        return;

    if (this->endPos != nullptr)
        this->grid[this->endPos->x][this->endPos->y].state = CellState::EMPTY;

    endPos = new sf::Vector2i(row, col);
    _bfs.setEnd(*endPos);
    this->grid[row][col].state = CellState::END;
}

void Surface::save() {
}