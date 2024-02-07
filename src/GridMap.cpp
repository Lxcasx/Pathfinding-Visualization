//
// Created by Lucas Heinschke on 01.02.24.
//

#include "GridMap.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "Grid.h"
#include "DEFINITIONS.h"

bool GridMap::load(const std::string &tileset, sf::Vector2u tileSize, GridRef grid, unsigned int width,
                   unsigned int height) {
    if (!_texture.loadFromFile(tileset))
        return false;

    this->tileSize = tileSize;
    this->width = width;
    this->height = height;

    int vertSize = width / tileSize.x * height / tileSize.x * 4;

    // resize the vertex array to fit the level size
    _vertices.setPrimitiveType(sf::Quads);
    _vertices.resize(vertSize);

    // populate the vertex array, with two triangles per tile
    update(grid);

    return true;
}

void GridMap::update(GridRef grid) {
    int rows = width / tileSize.x;
    int cols = height / tileSize.x;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            CellField field = (*grid)[i][j];
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

void GridMap::updateTile(GridRef grid, Cell cell) {
    int cols = height / tileSize.x;

    CellField field = (*grid)[cell.row][cell.col];
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

    // apply the tileset texture
    //states.texture = &_texture;

    // draw the vertex array
    target.draw(_vertices, states);
}

sf::VertexArray GridMap::getRect(int row, int col, sf::Color color) const {
    sf::VertexArray rect(sf::Quads, 4);
    int size = tileSize.x;

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
            break;
        case CellState::START:
            return COLOR_START;
            break;
        case CellState::END:
            return COLOR_END;
            break;
        case CellState::PATH:
            return COLOR_PATH;
            break;
        default:
            if (field.visited) {
                return COLOR_VISITED;
            } else {
                return COLOR_BG;
            }
            break;
    }
}