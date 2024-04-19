//
// Created by Lucas Heinschke on 15.02.24.
//

#include "Pathfinding.h"

namespace path
{
    Pathfinding::Pathfinding(GridMap *map) : _map(map)
    {
    }

    void Pathfinding::setStart(Cell start)
    {
        // ToDo: if path finding is running it should be started again
        _start = start;
    }

    void Pathfinding::setEnd(Cell end)
    {
        // ToDo: if path finding is running it should be started again
        _end = end;
    }
}