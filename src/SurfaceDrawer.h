//
// Created by lucas on 29.01.24.
//

#ifndef PATHFINDING_SURFACEDRAWER_H
#define PATHFINDING_SURFACEDRAWER_H


#include <memory>
#include "Grid.h"
#include "Game.h"

class SurfaceDrawer {
public:
    SurfaceDrawer(GameDataRef data, GridRef grid);

    void setSize(int rows, int cols, int size);

    void draw(float dt);

private:
    GameDataRef _data;
    GridRef _grid;
    int _rows{};
    int _cols{};
    int _size{};
    sf::RectangleShape cellShape;
};

#endif //PATHFINDING_SURFACEDRAWER_H
