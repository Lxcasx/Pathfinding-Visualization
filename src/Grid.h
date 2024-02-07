//
// Created by lucas on 29.01.24.
//

#pragma once
#ifndef PATHFINDING_GRID_H
#define PATHFINDING_GRID_H

#include <memory>
#include "vector"
#include "SFML/Graphics.hpp"

using namespace std;

enum CellState {
    EMPTY,
    WALL,
    START,
    END,
    PATH
};

class Cell {
public:
    int row;
    int col;

    bool operator==(const Cell &lhs) const {
        return lhs.row == row && lhs.col == col;
    }

    bool operator!=(const Cell &lhs) const {
        return lhs.row != row && lhs.col != col;
    }

    Cell operator+(const Cell &lhs) const {
        return Cell{
                row + lhs.row,
                col + lhs.col
        };
    }
};

struct CellField {
    CellState state = CellState::EMPTY;
    bool visited = false;
    Cell parent = {-1, -1};
};

typedef vector<vector<CellField>> Grid;
typedef Grid *GridRef;

#endif //PATHFINDING_GRID_H
