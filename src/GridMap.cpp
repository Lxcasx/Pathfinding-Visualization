//
// Created by Lucas Heinschke on 01.02.24.
//

#include "GridMap.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "Grid.h"
#include "DEFINITIONS.h"

bool GridMap::load(sf::Vector2u tileSize, unsigned int width, unsigned int height) {
    _tileSize = tileSize;
    _width = width;
    _height = height;

    int gridSize = width / tileSize.x * height / tileSize.x;
    int vertSize = gridSize * 4;

    // resize the vertex array to fit the level size
    _vertices.setPrimitiveType(sf::Quads);
    _vertices.resize(vertSize);

    // resize grid array to fit the level size
    _grid->resize(gridSize);

    for (int i = 0; i < this->rows; i++) {
        std::vector <CellField> row;

        for (int j = 0; j < this->cols; j++) {
            if (j == 0 || j == this->cols - 1 || i == 0 || i == this->rows - 1)
                row.push_back(CellField{CellState::WALL});
            else
                row.push_back(CellField{CellState::EMPTY});
        }

        grid->push_back(row);
    }

    update();

    return true;
}

void GridMap::update() {
    int rows = _width / _tileSize.x;
    int cols = _height / _tileSize.x;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            CellField field = _grid->at(i).at(j);
            sf::Color color = getColor(field);
            sf::VertexArray rect = getRect(i, j, color);

            // map index of 2 dimensional array to one dimensional
            unsigned int p = i * cols + j;

            // create 4 vertices per element
            for (int k = 0; k < 4; ++k) {
                unsigned int index = (p * 4) + k;

                _vertices[index] = rect[k];
            }
        }
    }
}

void GridMap::updateTile(Cell cell) {
    int cols = _height / _tileSize.x;

    CellField field = (*_grid)[cell.row][cell.col];
    sf::Color color = getColor(field);
    sf::VertexArray rect = getRect(cell.row, cell.col, color);

    // map index of 2 dimensional array to one dimensional
    unsigned int p = cell.row * cols + cell.col;

    // create 4 vertices per element
    for (int k = 0; k < 4; ++k) {
        unsigned int index = (p * 4) + k;

        _vertices[index] = rect[k];
    }
}

void GridMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();

    // draw the vertex array
    target.draw(_vertices, states);
}

sf::VertexArray GridMap::getRect(int row, int col, sf::Color color) const {
    sf::VertexArray rect(sf::Quads, 4);
    int size = _tileSize.x;

    float x1 = row * size;
    float y1 = col * size;

    float x2 = row * size;
    float y2 = col * size + size;

    float x3 = row * size + size;
    float y3 = col * size + size;

    float x4 = row * size + size;
    float y4 = col * size;

    rect[0].position = sf::Vector2f(x1, y1);
    rect[1].position = sf::Vector2f(x2, y2);
    rect[2].position = sf::Vector2f(x3, y3);
    rect[3].position = sf::Vector2f(x4, y4);

    rect[0].color = color;
    rect[1].color = color;
    rect[2].color = color;
    rect[3].color = color;

    return rect;
}


sf::Color GridMap::getColor(CellField field) {
    switch (field.state) {
        case CellState::WALL:
            return COLOR_WALL;
        case CellState::START:
            return COLOR_START;
        case CellState::END:
            return COLOR_END;
        case CellState::PATH:
            return COLOR_PATH;
        default:
            if (field.visited) {
                return COLOR_VISITED;
            } else {
                return COLOR_BG;
            }
    }
}

void GridMap::setStart(sf::Vector2i pos) {
    Cell cell{};

    if (!isPositionInGrid(pos, &cell)) {
        return;
    }

    setStart(cell);
}

void GridMap::setWall(sf::Vector2i pos) {
    Cell cell{};

    if (!isPositionInGrid(pos, &cell)) {
        return;
    }

    setWall(cell);
}

void GridMap::setWall(Cell pos) {
    if (lastPos != Cell{-1, -1}) {
        correctWall(pos, lastPos);
    }

    lastPos = pos;
    setCellField(pos, CellState::WALL);
}

void GridMap::setStart(Cell cell) {
    CellField field = _grid->at(cell.row).at(cell.col);

    if (field.state == CellState::WALL || field.state == CellState::END)
        return;

    // delete old start position
    if (startPos != Cell{-1, -1}) {
        setCellField(startPos, CellState::EMPTY);
    }

    startPos = cell;
    //_path.setStart(startPos);

    setCellField(cell, CellState::START);
}

void GridMap::setEnd(sf::Vector2i pos) {
    Cell cell{};

    if (!isPositionInGrid(pos, &cell)) {
        return;
    }

    setEnd(cell);
}

void GridMap::setEnd(Cell cell) {
    CellField field = _grid->at(cell.row).at(cell.col);

    if (field.state == CellState::WALL || field.state == CellState::START)
        return;

    // delete old start position
    if (endPos != Cell{-1, -1}) {
        setCellField(endPos, CellState::EMPTY);
    }

    endPos = cell;
    //_path.setEnd(endPos);

    setCellField(cell, CellState::END);
}

// Correct the placement of walls that were not captured by the loop using the bresenham line algorithm.
void GridMap::correctWall(Cell start, Cell end) {
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

bool GridMap::isPositionInGrid(sf::Vector2i pos, Cell *cell) const {
    const int row = pos.x / _tileSize.x;
    const int col = pos.y / _tileSize.x;
    const int rows = _width / _tileSize.x;
    const int cols = _height / _tileSize.x;

    if (row < 0 || col < 0)
        return false;
    if (row >= rows || col >= cols)
        return false;

    cell->row = row;
    cell->col = col;

    return true;
}

void GridMap::setCellField(Cell cell, CellState state) {
    (*_grid)[cell.row][cell.col].state = state;
    (*_grid)[cell.row][cell.col].visited = false;

    updateTile(cell);
}