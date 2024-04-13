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
        BFSFinding(GridRef grid);

        void setStart(Cell start);

        void setEnd(Cell end);

        void nextStep();

        std::vector<Cell> constructPath();

        void clear();

        bool finished = false;

    private:
        GridRef _grid;
        Cell start;
        Cell end;
        std::queue<Cell> queue;

        void markVisited(Cell cell);
    };
}
#endif //PATHFINDING_BFSFINDING_H
