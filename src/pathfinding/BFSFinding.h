//
// Created by lucas on 29.01.24.
//

#ifndef PATHFINDING_BFSFINDING_H
#define PATHFINDING_BFSFINDING_H

#include "../Grid.h"
#include "Pathfinding.h"
#include "SFML/Graphics.hpp"
#include "queue"

namespace path
{
    class BFSFinding : public Pathfinding
    {
    public:
        BFSFinding(GridMap *map);
        void setStart(Cell start) override;
        void setEnd(Cell start) override;
        void clear() override;
        void nextStep() override;
        void constructPath() override;

    private:
        std::queue<Cell> queue;

        void markVisited(Cell cell);
    };
}
#endif // PATHFINDING_BFSFINDING_H
