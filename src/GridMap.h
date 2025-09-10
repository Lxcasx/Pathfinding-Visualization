//
// Created by Lucas Heinschke on 01.02.24.
//

#ifndef PATHFINDING_GRIDMAP_H
#define PATHFINDING_GRIDMAP_H

#include "SFML/Graphics.hpp"
#include "Grid.h"
#include <unordered_set>

class GridMap : public sf::Drawable, public sf::Transformable
{
public:
    GridMap(GridRef grid);

    bool load(sf::Vector2u tileSize, unsigned int width, unsigned int height);

    void setVisitedTile(Cell cell);

    void setTile(Cell cell, CellState state);

    void update();

    void updateTile(Cell cell);

    void markDirty(Cell cell);

    void flushDirtyTiles();

    void flushDirtyTilesImmediate(); // For path construction

    const std::unordered_set<unsigned int>& getDirtyTiles() const { return _dirtyTiles; }

    void setFullUpdateNeeded() { _fullUpdateNeeded = true; _dirtyTiles.clear(); }

    GridRef _grid;

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    sf::VertexArray getRect(int row, int col, sf::Color color) const;

    sf::Color getColor(CellField field);

    void updateSingleTile(Cell cell);

    sf::VertexArray _vertices;
    sf::Vector2u _tileSize;
    unsigned int _width;
    unsigned int _height;
    
    // Performance optimization: track dirty tiles
    std::unordered_set<unsigned int> _dirtyTiles;
    bool _fullUpdateNeeded;
    
    // Cached colors for performance
    static sf::Color _cachedColors[6]; // EMPTY, WALL, START, END, PATH, VISITED
    static bool _colorsInitialized;
};

#endif // PATHFINDING_GRIDMAP_H
