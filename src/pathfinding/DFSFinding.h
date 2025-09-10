//
// Created by Lucas Heinschke on 10.09.25.
//

#ifndef PATHFINDING_DFSFINDING_H
#define PATHFINDING_DFSFINDING_H

#include "../Grid.h"
#include "Pathfinding.h"
#include "SFML/Graphics.hpp"
#include <stack>

namespace path
{
    class DFSFinding : public Pathfinding
    {
    public:
        DFSFinding(GridMap *map);
        void setStart(Cell start) override;
        void setEnd(Cell start) override;
        void clear() override;
        void nextStep() override;
        void constructPath() override;

    private:
        std::stack<Cell> stack;
        int _stepCounter;
        int _batchSize;

        void markVisited(Cell cell);
    };
}

#endif // PATHFINDING_DFSFINDING_H
