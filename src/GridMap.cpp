//
// Created by Lucas Heinschke on 01.02.24.
//

#include "GridMap.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "Grid.h"
#include "DEFINITIONS.h"

GridMap::GridMap(GridRef grid) : _grid(grid)
{
}

bool GridMap::load(sf::Vector2u tileSize, unsigned int width, unsigned int height)
{
    _tileSize = tileSize;
    _width = width;
    _height = height;

    int vertCount = width / tileSize.x * height / tileSize.x * 4;

    // resize the vertex array to fit the level size
    _vertices.setPrimitiveType(sf::Quads);
    _vertices.resize(vertCount);

    // populate the vertex array, with two triangles per tile
    update();

    return true;
}

void GridMap::update()
{
    int rows = _width / _tileSize.x;
    int cols = _height / _tileSize.x;

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            CellField field = (*_grid)[i][j];
            sf::Color color = getColor(field);
            sf::VertexArray rect = getRect(i, j, color);

            // map index of 2 dimensional array to one dimensional
            unsigned int p = i * cols + j;

            // create 4 vertices per element
            for (int k = 0; k < 4; ++k)
            {
                unsigned int index = (p * 4) + k;

                _vertices[index] = rect[k];
            }
        }
    }
}

void GridMap::setVisitedTile(Cell cell)
{
    CellField *field = &(*_grid)[cell.row][cell.col];

    if (field->state == CellState::EMPTY)
    {
        field->visited = true;
        updateTile(cell);
    }
}

void GridMap::setTile(Cell cell, CellState state)
{
    (*_grid)[cell.row][cell.col].state = state;
    (*_grid)[cell.row][cell.col].visited = false;

    updateTile(cell);
}

void GridMap::updateTile(Cell cell)
{
    int cols = _height / _tileSize.x;

    CellField field = (*_grid)[cell.row][cell.col];
    sf::Color color = getColor(field);
    sf::VertexArray rect = getRect(cell.row, cell.col, color);

    // map index of 2 dimensional array to one dimensional
    unsigned int p = cell.row * cols + cell.col;

    // create 4 vertices per element
    for (int k = 0; k < 4; ++k)
    {
        unsigned int index = (p * 4) + k;

        _vertices[index] = rect[k];
    }
}

void GridMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    // draw the vertex array
    target.draw(_vertices, states);
}

sf::VertexArray GridMap::getRect(int row, int col, sf::Color color) const
{
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

sf::Color GridMap::getColor(CellField field)
{
    if (field.visited)
        return COLOR_VISITED;

    switch (field.state)
    {
    case CellState::WALL:
        return COLOR_WALL;
    case CellState::START:
        return COLOR_START;
    case CellState::END:
        return COLOR_END;
    case CellState::PATH:
        return COLOR_PATH;
    default:
        return COLOR_BG;
    }
}