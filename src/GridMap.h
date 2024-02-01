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
    load(const std::string &tileset, sf::Vector2u tileSize, GridRef grid, unsigned int width,
         unsigned int height);

    void update(GridRef grid);

private:
    sf::VertexArray _vertices;
    sf::Texture _texture;
    unsigned int width;
    unsigned int height;
    sf::Vector2u tileSize;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    sf::VertexArray getRect(int row, int col, sf::Color color) const;

    sf::Color getColor(CellField field);
};


#endif //PATHFINDING_GRIDMAP_H
