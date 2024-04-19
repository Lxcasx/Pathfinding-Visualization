//
// Created by lucas on 29.01.24.
//

#ifndef PATHFINDING_SURFACE_H
#define PATHFINDING_SURFACE_H

#include "Game.h"
#include "Grid.h"
#include "pathfinding/Pathfinding.h"
#include "pathfinding/BFSFinding.h"
#include "GridMap.h"

class Surface
{
public:
    Surface(GameDataRef data);

    void init(int width, int height);

    void setPosition(float x, float y);

    void handleInput();

    void update(float dt);

    void draw(float dt);

    void clear();

    void save();

private:
    GameDataRef _data;
    GridRef _grid = new Grid();
    GridMap _map;
    path::BFSFinding _path;

    int rows{};
    int cols{};
    int _width{};
    int _height{};
    Cell lastPos = {-1, -1};
    Cell startPos = {-1, -1};
    Cell endPos = {-1, -1};
    std::vector<int> level;

    void prepare();

    void correctWall(Cell start, Cell end);

    void setWall(sf::Vector2i pos);

    void setWall(Cell cell);

    void setStart(sf::Vector2i pos);

    void setStart(Cell cell);

    void setEnd(sf::Vector2i pos);

    void setEnd(Cell cell);

    void setCellField(Cell cell, CellState state);

    bool isPositionInGrid(sf::Vector2i pos, Cell *cell) const;
};

#endif // PATHFINDING_SURFACE_H
