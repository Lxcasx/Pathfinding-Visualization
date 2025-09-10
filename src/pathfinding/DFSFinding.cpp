//
// Created by Lucas Heinschke on 10.09.25.
//

#include <stack>
#include "DFSFinding.h"
#include "plog/Log.h"
#include "../DEFINITIONS.h"

namespace path
{
    DFSFinding::DFSFinding(GridMap *map) : Pathfinding(map) {}

    void DFSFinding::setStart(Cell start)
    {
        clear();
        _start = start;
        stack.push(start);
    }

    void DFSFinding::setEnd(Cell end)
    {
        _end = end;
    }

    void DFSFinding::clear()
    {
        isFinished = false;
        pathConstructed = false;
        stack = {};
        _stepCounter = 0;
        _batchSize = PATHFINDING_BATCH_SIZE;
    }

    void DFSFinding::nextStep()
    {
        std::vector<Cell> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // 4 possible directions
        
        // Process multiple cells per frame for better performance
        for (int batch = 0; batch < _batchSize && !stack.empty(); ++batch)
        {
            Cell current = stack.top();
            stack.pop();

            // Skip if already visited
            if (_map->_grid->at(current.row).at(current.col).visited)
                continue;

            // Mark as visited
            markVisited(current);

            // Check if we reached the end
            if (current == _end)
            {
                isFinished = true;
                return;
            }

            // Add neighbors to stack (in reverse order for consistent direction preference)
            for (int i = directions.size() - 1; i >= 0; --i)
            {
                Cell neighbor = current + directions[i];

                // Bounds checking
                if (neighbor.row < 0 || neighbor.col < 0 || 
                    neighbor.row >= _map->_grid->size() || 
                    neighbor.col >= _map->_grid->at(0).size())
                    continue;

                // Check if the neighbor is valid
                if (_map->_grid->at(neighbor.row).at(neighbor.col).state != WALL &&
                    !_map->_grid->at(neighbor.row).at(neighbor.col).visited)
                {
                    stack.push(neighbor);
                    _map->_grid->at(neighbor.row).at(neighbor.col).parent = current;
                }
            }
        }
        
        // If stack is empty and we haven't found the end, no path exists
        if (stack.empty() && !isFinished)
        {
            isFinished = true;
            PLOGI << "DFS pathfinding completed - no path found";
        }

        _stepCounter++;
    }

    void DFSFinding::markVisited(Cell cell)
    {
        _map->setVisitedTile(cell);
    }

    void DFSFinding::constructPath()
    {
        if (pathConstructed) return; // Don't construct path multiple times
        
        std::vector<Cell> path;

        // Safety check: ensure we have a valid path before constructing
        Cell current = _end;
        int maxIterations = _map->_grid->size() * _map->_grid->at(0).size(); // Prevent infinite loops
        int iterations = 0;
        
        while (current != _start && iterations < maxIterations)
        {
            path.push_back(current);
            Cell parent = _map->_grid->at(current.row).at(current.col).parent;
            
            // Check if parent is valid
            if (parent.row == -1 && parent.col == -1) {
                // Invalid parent, path is broken
                PLOGE << "DFS path reconstruction failed: invalid parent chain";
                return;
            }
            
            current = parent;
            iterations++;
        }
        
        if (iterations >= maxIterations) {
            PLOGE << "DFS path reconstruction failed: maximum iterations reached";
            return;
        }
        
        path.push_back(_start);                 // don't forget to add the start cell
        std::reverse(path.begin(), path.end()); // reverse the path to start from the beginning

        // Batch path updates for better performance
        for (const Cell &cell : path)
        {
            if (cell == _start || cell == _end)
                continue;

            _map->setTile(cell, CellState::PATH);
        }
        
        pathConstructed = true;
        PLOGI << "DFS path constructed successfully with " << path.size() << " cells";
    }
}
