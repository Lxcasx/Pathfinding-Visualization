//
// Created by Lucas Heinschke on 15.02.24.
//

#ifndef PATHFINDING_PATHFINDING_H
#define PATHFINDING_PATHFINDING_H

#include "../Grid.h"

namespace path {
    class Pathfinding {
    public:
        Pathfinding(GridRef grid);

        virtual void setStart(Cell start);

        virtual void setEnd(Cell end);

        virtual void clear() = 0;

        virtual void nextStep() = 0;

        virtual void constructPath() = 0;

        bool isFinished{};

    private:
    protected:
        Cell _start{};
        Cell _end{};
        GridRef _grid;
    };
}

#endif //PATHFINDING_PATHFINDING_H
