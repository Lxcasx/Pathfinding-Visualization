//
// Created by Lucas Heinschke on 01.02.24.
//

#ifndef PATHFINDING_GRIDMAP_H
#define PATHFINDING_GRIDMAP_H

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "Grid.h"

class GridMap : public sf::Drawable, public sf::Transformable
{
public:
    GridMap(GridRef grid);
    bool load(sf::Vector2u tileSize, unsigned int width, unsigned int height);
    void update();
    void updateTile(Cell cell);
    void setTile(Cell cell, CellState state);
    void setVisitedTile(Cell cell);
    GridRef _grid;

private:
    sf::VertexArray _vertices;
    sf::Texture _texture;
    unsigned int _width;
    unsigned int _height;
    sf::Vector2u _tileSize;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::VertexArray getRect(int row, int col, sf::Color color) const;

    sf::Color getColor(CellField field);
};

#endif // PATHFINDING_GRIDMAP_H
