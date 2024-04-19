//
// Created by lucas on 29.01.24.
//

#include <list>
#include <queue>
#include <utility>
#include "BFSFinding.h"
#include "plog/Log.h"

namespace path
{
    BFSFinding::BFSFinding(GridMap *map) : Pathfinding(map) {}

    void BFSFinding::setStart(Cell start)
    {
        clear();
        _start = start;
        queue.push(start);
    }

    void BFSFinding::setEnd(Cell end)
    {
        _end = end;
    }

    void BFSFinding::clear()
    {
        isFinished = false;
        queue = {};
    }

    void BFSFinding::nextStep()
    {
        std::vector<Cell> directions = {{-1, 0},
                                        {1, 0},
                                        {0, -1},
                                        {0, 1}}; // 4 possible directions
        Cell current = queue.front();
        queue.pop();

        // check if we reached the end
        if (current == _end)
        {
            isFinished = true;
            return;
        }

        // check all neighbors
        for (const Cell &direction : directions)
        {
            Cell neighbor = current + direction;

            // check if the neighbor is valid
            if (_map->_grid->at(neighbor.row).at(neighbor.col).state != WALL &&
                !_map->_grid->at(neighbor.row).at(neighbor.col).visited)
            {

                queue.push(neighbor);
                markVisited(neighbor);

                _map->_grid->at(neighbor.row).at(neighbor.col).parent = current;
            }
        }
    }

    void BFSFinding::markVisited(Cell cell)
    {
        _map->setVisitedTile(cell);
    }

    void BFSFinding::constructPath()
    {
        std::vector<Cell> path;

        for (Cell cell = _end; cell != _start; cell = _map->_grid->at(cell.row).at(cell.col).parent)
        {
            path.push_back(cell);
        }
        path.push_back(_start);                 // don't forget to add the start cell
        std::reverse(path.begin(), path.end()); // reverse the path to start from the beginning

        for (const Cell &cell : path)
        {
            if (cell == _start || cell == _end)
                continue;

            _map->setTile(cell, CellState::PATH);
        }
    }
}