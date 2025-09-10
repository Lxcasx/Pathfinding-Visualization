//
// Created by Lucas Heinschke on 10.09.25.
//

#include <cmath>
#include <limits>
#include "AStarFinding.h"
#include "plog/Log.h"
#include "../DEFINITIONS.h"

namespace path
{
    AStarFinding::AStarFinding(GridMap *map) : Pathfinding(map) {}

    void AStarFinding::setStart(Cell start)
    {
        clear();
        _start = start;
        
        gScores[cellToIndex(start)] = 0;
        fScores[cellToIndex(start)] = heuristic(start, _end);
        openSet.push({start, fScores[cellToIndex(start)], 0, heuristic(start, _end)});
    }

    void AStarFinding::setEnd(Cell end)
    {
        _end = end;
    }

    void AStarFinding::clear()
    {
        isFinished = false;
        pathConstructed = false;
        openSet = {};
        gScores.clear();
        fScores.clear();
        _stepCounter = 0;
        _batchSize = PATHFINDING_BATCH_SIZE;
    }

    void AStarFinding::nextStep()
    {
        std::vector<Cell> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // 4 possible directions
        
        // Process multiple cells per frame for better performance
        for (int batch = 0; batch < _batchSize && !openSet.empty(); ++batch)
        {
            AStarNode current = openSet.top();
            openSet.pop();

            // Check if we reached the end
            if (current.cell == _end)
            {
                isFinished = true;
                return;
            }

            // Mark as visited
            markVisited(current.cell);

            // Check all neighbors
            for (const Cell &direction : directions)
            {
                Cell neighbor = current.cell + direction;

                // Bounds checking
                if (neighbor.row < 0 || neighbor.col < 0 || 
                    neighbor.row >= _map->_grid->size() || 
                    neighbor.col >= _map->_grid->at(0).size())
                    continue;

                // Skip walls and visited cells
                if (_map->_grid->at(neighbor.row).at(neighbor.col).state == WALL ||
                    _map->_grid->at(neighbor.row).at(neighbor.col).visited)
                    continue;

                float tentativeGScore = current.gCost + 1.0f; // Distance between neighbors is 1
                unsigned int neighborIndex = cellToIndex(neighbor);

                // If this path to neighbor is better than any previous one
                if (gScores.find(neighborIndex) == gScores.end() || 
                    tentativeGScore < gScores[neighborIndex])
                {
                    // Record the best path
                    _map->_grid->at(neighbor.row).at(neighbor.col).parent = current.cell;
                    gScores[neighborIndex] = tentativeGScore;
                    
                    float hCost = heuristic(neighbor, _end);
                    float fCost = tentativeGScore + hCost;
                    fScores[neighborIndex] = fCost;

                    openSet.push({neighbor, fCost, tentativeGScore, hCost});
                }
            }
        }
        
        // If openSet is empty and we haven't found the end, no path exists
        if (openSet.empty() && !isFinished)
        {
            isFinished = true;
            PLOGI << "A* pathfinding completed - no path found";
        }

        _stepCounter++;
    }

    void AStarFinding::markVisited(Cell cell)
    {
        _map->setVisitedTile(cell);
    }

    void AStarFinding::constructPath()
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
                PLOGE << "A* path reconstruction failed: invalid parent chain";
                return;
            }
            
            current = parent;
            iterations++;
        }
        
        if (iterations >= maxIterations) {
            PLOGE << "A* path reconstruction failed: maximum iterations reached";
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
        PLOGI << "A* path constructed successfully with " << path.size() << " cells";
    }

    float AStarFinding::heuristic(Cell a, Cell b)
    {
        // Manhattan distance heuristic
        return std::abs(a.row - b.row) + std::abs(a.col - b.col);
    }

    unsigned int AStarFinding::cellToIndex(Cell cell)
    {
        return cell.row * _map->_grid->at(0).size() + cell.col;
    }
}
