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

class GridMap : public sf::Drawable, public sf::Transformable {
public:
    bool
    load(sf::Vector2u tileSize, unsigned int width, unsigned int height);

    void update();

    void updateTile(Cell cell);

    void setWall(sf::Vector2i pos);

private:
    sf::VertexArray _vertices;
    unsigned int _width;
    unsigned int _height;
    sf::Vector2u _tileSize;
    GridRef _grid = new Grid();
    Cell lastPos = {-1, -1};
    Cell startPos = {-1, -1};
    Cell endPos = {-1, -1};

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::VertexArray getRect(int row, int col, sf::Color color) const;

    sf::Color getColor(CellField field);

    void setStart(sf::Vector2i pos);

    void setStart(Cell cell);

    void setEnd(sf::Vector2i pos);

    void setEnd(Cell cell);

    void correctWall(Cell start, Cell end);

    void setWall(Cell cell);

    bool isPositionInGrid(sf::Vector2i pos, Cell *cell) const;

    void setCellField(Cell cell, CellState state);
};


#endif //PATHFINDING_GRIDMAP_H
