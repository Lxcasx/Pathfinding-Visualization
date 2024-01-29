//
// Created by lucas on 29.01.24.
//

#ifndef PATHFINDING_BFSFINDING_H
#define PATHFINDING_BFSFINDING_H

#include "../Grid.h"
#include "SFML/Graphics.hpp"
#include "queue"

namespace path {
    class BFSFinding {
    public:
        BFSFinding(Grid *grid);

        void setStart(sf::Vector2i start);

        void setEnd(sf::Vector2i end);

        void nextStep();

        std::vector<sf::Vector2i> constructPath();

        void clear();

        bool finished = false;

    private:
        Grid *_grid;
        sf::Vector2i start;
        sf::Vector2i end;
        std::queue<sf::Vector2i> queue;

        void markVisited(sf::Vector2i cell);
    };
}
#endif //PATHFINDING_BFSFINDING_H
