//
// Created by Lucas Heinschke on 15.02.24.
//

#ifndef PATHFINDING_DIJKSTRAFINDING_H
#define PATHFINDING_DIJKSTRAFINDING_H

#include "Pathfinding.h"
#include "queue"

namespace path {
    class DijkstraFinding : public Pathfinding {
    public:
        DijkstraFinding(GridRef grid);

        void setStart(Cell start) override;

        void clear() override;

        void nextStep() override;

        void constructPath() override;

    private:
        std::queue<Cell> queue;
    };
}


#endif //PATHFINDING_DIJKSTRAFINDING_H
