//
// Created by lucas on 29.01.24.
//

#ifndef PATHFINDING_SURFACE_H
#define PATHFINDING_SURFACE_H


#include "Game.h"
#include "Grid.h"
#include "pathfinding/BFSFinding.h"

class Surface {
public:
    Surface(GameDataRef data);

    void init(int width, int height, float size);

    void setPosition(float x, float y);

    void handleInput();

    void draw(float dt);

    void setWall(sf::Vector2i pos);

    void setStart(sf::Vector2i pos);

    void setEnd(sf::Vector2i pos);

    void clear();

    void save();

private:
    GameDataRef _data;
    Grid grid;
    int rows;
    int cols;
    int width;
    int height;
    float size;
    sf::Vector2i *lastPos = nullptr;
    sf::Vector2i *startPos = nullptr;
    sf::Vector2i *endPos = nullptr;
    path::BFSFinding _bfs;

    void prepare();
};


#endif //PATHFINDING_SURFACE_H
