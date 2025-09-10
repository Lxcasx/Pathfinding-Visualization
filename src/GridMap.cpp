//
// Created by Lucas Heinschke on 01.02.24.
//

#include "GridMap.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "Grid.h"
#include "DEFINITIONS.h"

// Static member initialization
sf::Color GridMap::_cachedColors[6];
bool GridMap::_colorsInitialized = false;

GridMap::GridMap(GridRef grid) : _grid(grid), _fullUpdateNeeded(true)
{
    // Initialize cached colors once
    if (!_colorsInitialized) {
        _cachedColors[0] = COLOR_BG;      // EMPTY
        _cachedColors[1] = COLOR_WALL;    // WALL
        _cachedColors[2] = COLOR_START;   // START
        _cachedColors[3] = COLOR_END;     // END
        _cachedColors[4] = COLOR_PATH;    // PATH
        _cachedColors[5] = COLOR_VISITED; // VISITED (used when field.visited == true)
        _colorsInitialized = true;
    }
}

bool GridMap::load(sf::Vector2u tileSize, unsigned int width, unsigned int height)
{
    _tileSize = tileSize;
    _width = width;
    _height = height;

    int vertCount = width / tileSize.x * height / tileSize.x * 6; // 6 vertices per tile (2 triangles)

    // resize the vertex array to fit the level size
    _vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    _vertices.resize(vertCount);

    // populate the vertex array, with two triangles per tile
    update();

    return true;
}

void GridMap::update()
{
    if (_fullUpdateNeeded) {
        // Full update - rebuild entire vertex array
        int rows = _width / _tileSize.x;
        int cols = _height / _tileSize.x;

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                updateSingleTile(Cell{i, j});
            }
        }
        _fullUpdateNeeded = false;
    } else {
        // Only update dirty tiles
        flushDirtyTiles();
    }
}

void GridMap::flushDirtyTiles()
{
    int cols = _height / _tileSize.x;
    int updatedCount = 0;
    
    // Rate limit tile updates for consistent performance (only for visited tiles)
    auto it = _dirtyTiles.begin();
    while (it != _dirtyTiles.end() && updatedCount < MAX_DIRTY_TILES_PER_FRAME) {
        unsigned int tileIndex = *it;
        int i = tileIndex / cols;
        int j = tileIndex % cols;
        updateSingleTile(Cell{i, j});
        
        it = _dirtyTiles.erase(it);
        updatedCount++;
    }
}

void GridMap::flushDirtyTilesImmediate()
{
    int cols = _height / _tileSize.x;
    
    // Update all dirty tiles immediately (for path construction)
    for (unsigned int tileIndex : _dirtyTiles) {
        int i = tileIndex / cols;
        int j = tileIndex % cols;
        updateSingleTile(Cell{i, j});
    }
    
    _dirtyTiles.clear();
}

void GridMap::markDirty(Cell cell)
{
    int cols = _height / _tileSize.x;
    unsigned int tileIndex = cell.row * cols + cell.col;
    _dirtyTiles.insert(tileIndex);
}

void GridMap::updateSingleTile(Cell cell)
{
    int cols = _height / _tileSize.x;
    
    CellField field = (*_grid)[cell.row][cell.col];
    sf::Color color = getColor(field);
    sf::VertexArray rect = getRect(cell.row, cell.col, color);

    // map index of 2 dimensional array to one dimensional
    unsigned int p = cell.row * cols + cell.col;

    // create 6 vertices per element (2 triangles)
    for (int k = 0; k < 6; ++k)
    {
        unsigned int index = (p * 6) + k;
        _vertices[index] = rect[k];
    }
}

void GridMap::setVisitedTile(Cell cell)
{
    CellField *field = &(*_grid)[cell.row][cell.col];

    if (field->state == CellState::EMPTY)
    {
        field->visited = true;
        markDirty(cell);
    }
}

void GridMap::setTile(Cell cell, CellState state)
{
    (*_grid)[cell.row][cell.col].state = state;
    (*_grid)[cell.row][cell.col].visited = false;

    markDirty(cell);
}

void GridMap::updateTile(Cell cell)
{
    markDirty(cell);
}

void GridMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    // draw the vertex array
    target.draw(_vertices, states);
}

sf::VertexArray GridMap::getRect(int row, int col, sf::Color color) const
{
    sf::VertexArray rect(sf::PrimitiveType::Triangles, 6);
    const float size = static_cast<float>(_tileSize.x);

    const float x1 = row * size;
    const float y1 = col * size;
    const float x2 = x1 + size;
    const float y2 = y1 + size;

    // First triangle (top-left, bottom-left, top-right)
    rect[0].position = sf::Vector2f(x1, y1);         // top-left
    rect[1].position = sf::Vector2f(x1, y2);         // bottom-left  
    rect[2].position = sf::Vector2f(x2, y1);         // top-right

    // Second triangle (bottom-left, bottom-right, top-right)
    rect[3].position = sf::Vector2f(x1, y2);         // bottom-left
    rect[4].position = sf::Vector2f(x2, y2);         // bottom-right
    rect[5].position = sf::Vector2f(x2, y1);         // top-right

    // Set color for all vertices
    for (int i = 0; i < 6; ++i) {
        rect[i].color = color;
    }

    return rect;
}

sf::Color GridMap::getColor(CellField field)
{
    // Use cached colors for better performance
    // Path tiles have priority over visited state
    if (field.state == CellState::PATH)
        return _cachedColors[4]; // PATH
    
    if (field.visited && field.state == CellState::EMPTY)
        return _cachedColors[5]; // VISITED
    
    return _cachedColors[static_cast<int>(field.state)];
}