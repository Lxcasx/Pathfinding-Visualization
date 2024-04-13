//
// Created by Lucas Heinschke on 15.02.24.
//

#include "DijkstraFinding.h"

namespace path {
    const int INF = numeric_limits<int>::max();

    DijkstraFinding::DijkstraFinding(GridRef grid) : Pathfinding(grid) {};

    void DijkstraFinding::setStart(Cell start) {
        _start = start;
        _queue.push(start);
    }

    void DijkstraFinding::constructPath() {

    }

    void DijkstraFinding::clear() {
        _queue = {};
    }

    void DijkstraFinding::nextStep() {
        return;
        std::vector<Cell> directions = {{-1, 0},
                                        {1,  0},
                                        {0,  -1},
                                        {0,  1}}; // 4 mögliche Richtungen

        Cell current = _queue.front();
        _queue.pop();

        if (current == _end) {
            isFinished = true;
            return;
        }

        for (const Cell &direction: directions) {
            Cell neighbor = current + direction;

            _queue.push(neighbor);
            markVisited(neighbor);
        }
    }

    void DijkstraFinding::markVisited(Cell cell) {
        this->_grid->at(cell.row).at(cell.col).visited = true;
    }
}