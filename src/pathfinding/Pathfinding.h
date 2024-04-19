//
// Created by Lucas Heinschke on 15.02.24.
//

#ifndef PATHFINDING_PATHFINDING_H
#define PATHFINDING_PATHFINDING_H

#include "../Grid.h"
#include "../GridMap.h"

namespace path {
    class Pathfinding {
    public:
        Pathfinding(GridMap* map);

        virtual void setStart(Cell start);

        virtual void setEnd(Cell end);

        virtual void clear() = 0;

        virtual void nextStep() = 0;

        virtual void constructPath() = 0;

        bool isFinished{};

    protected:
        Cell _start{};
        Cell _end{};
        GridMap* _map;
    };
}

#endif //PATHFINDING_PATHFINDING_H
