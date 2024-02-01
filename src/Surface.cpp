//
// Created by lucas on 29.01.24.
//

#include "Surface.h"
#include "pathfinding/BFSFinding.h"
#include "plog/Log.h"
#include <cmath>
#include <chrono>

Surface::Surface(const GameDataRef &data) : _data(data), _bfs(grid) {
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
    map.load("resources/res/images/tileset.png", sf::Vector2u(20, 20), grid, width, height);
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
    auto start = std::chrono::high_resolution_clock::now();

    _data->window.draw(map);

    if (this->startPos != Cell{-1, -1} && this->endPos != Cell{-1, -1} && !_bfs.finished) {
        _bfs.nextStep();
    }

    /*if (this->startPos != Cell{-1, -1} && this->endPos != Cell{-1, -1} && this->_bfs.finished) {
        std::vector<Cell> path = this->_bfs.constructPath();
    }*/

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    PLOGV << "Time taken by function: " << duration.count() << " microseconds";
}

void Surface::update(float dt) {

}

void Surface::setWall(sf::Vector2i pos) {
    Cell cell{};

    if (!isPositionInGrid(pos, &cell)) {
        return;
    }

    setWall(cell);
}

void Surface::setWall(Cell pos) {
    if (lastPos != Cell{-1, -1}) {
        this->correctWall(pos, lastPos);
    }

    lastPos = pos;
    setCellField(pos, CellState::WALL);
}

bool Surface::isPositionInGrid(sf::Vector2i pos, Cell *cell) const {
    int row = pos.x / this->size;
    int col = pos.y / this->size;

    if (row < 0 || col < 0)
        return false;
    if (row >= rows || col >= cols)
        return false;

    cell->row = row;
    cell->col = col;

    return true;
}

// Correct the placement of walls that were not captured by the loop using the bresenham line algorithm.
void Surface::correctWall(Cell start, Cell end) {
    int x1 = start.row;
    int y1 = start.col;
    int x2 = end.row;
    int y2 = end.col;

    int dx = std::abs(x2 - x1);
    int dy = std::abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while (true) {
        setCellField(Cell{x1, y1}, CellState::WALL);

        if (x1 == x2 && y1 == y2) {
            break;
        }

        int e2 = 2 * err;

        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
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
    this->_bfs.clear();
    this->startPos = Cell{-1, -1};
    this->endPos = Cell{-1, -1};
    map.update(grid);
}

void Surface::setStart(sf::Vector2i pos) {
    Cell cell{};

    if (!isPositionInGrid(pos, &cell)) {
        return;
    }

    setStart(cell);
}

void Surface::setStart(Cell cell) {
    CellField field = this->grid->at(cell.row).at(cell.col);

    if (field.state == CellState::WALL || field.state == CellState::END)
        return;

    // delete old start position
    if (startPos != Cell{-1, -1}) {
        setCellField(startPos, CellState::EMPTY);
    }

    startPos = cell;
    _bfs.setStart(startPos);

    setCellField(cell, CellState::START);
}

void Surface::setEnd(sf::Vector2i pos) {
    Cell cell{};

    if (!isPositionInGrid(pos, &cell)) {
        return;
    }

    setEnd(cell);
}

void Surface::setEnd(Cell cell) {
    CellField field = this->grid->at(cell.row).at(cell.col);

    if (field.state == CellState::WALL || field.state == CellState::START)
        return;

    // delete old start position
    if (endPos != Cell{-1, -1}) {
        setCellField(endPos, CellState::EMPTY);
    }

    endPos = cell;
    _bfs.setEnd(endPos);

    setCellField(cell, CellState::END);
}

void Surface::save() {
}

void Surface::setCellField(Cell cell, CellState state) {
    (*grid)[cell.row][cell.col].state = state;
    (*grid)[cell.row][cell.col].visited = false;

    map.update(grid);
}