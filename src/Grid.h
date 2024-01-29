//
// Created by lucas on 29.01.24.
//

#ifndef PATHFINDING_GRID_H
#define PATHFINDING_GRID_H

#include "vector"
#include "SFML/Graphics.hpp"

enum CellState {
    EMPTY,
    WALL,
    START,
    END,
    PATH
};

struct Cell {
    CellState state = CellState::EMPTY;
    bool visited = false;
    sf::Vector2i parent = {-1, -1};
};

typedef std::vector<std::vector<Cell>> Grid;


#endif //PATHFINDING_GRID_H
