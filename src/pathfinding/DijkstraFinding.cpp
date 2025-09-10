//
// Created by Lucas Heinschke on 10.09.25.
//

#include <limits>
#include "DijkstraFinding.h"
#include "plog/Log.h"
#include "../DEFINITIONS.h"

namespace path
{
    DijkstraFinding::DijkstraFinding(GridMap *map) : Pathfinding(map) {}

    void DijkstraFinding::setStart(Cell start)
    {
        clear();
        _start = start;
        
        distances[cellToIndex(start)] = 0;
        priorityQueue.push({start, 0});
    }

    void DijkstraFinding::setEnd(Cell end)
    {
        _end = end;
    }

    void DijkstraFinding::clear()
    {
        isFinished = false;
        pathConstructed = false;
        priorityQueue = {};
        distances.clear();
        _stepCounter = 0;
        _batchSize = PATHFINDING_BATCH_SIZE;
    }

    void DijkstraFinding::nextStep()
    {
        std::vector<Cell> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // 4 possible directions
        
        // Process multiple cells per frame for better performance
        for (int batch = 0; batch < _batchSize && !priorityQueue.empty(); ++batch)
        {
            DijkstraNode current = priorityQueue.top();
            priorityQueue.pop();

            // Skip if we already found a better path to this cell
            unsigned int currentIndex = cellToIndex(current.cell);
            if (distances.find(currentIndex) != distances.end() && 
                current.distance > distances[currentIndex])
                continue;

            // Mark as visited
            markVisited(current.cell);

            // Check if we reached the end
            if (current.cell == _end)
            {
                isFinished = true;
                return;
            }

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

                float newDistance = current.distance + 1.0f; // All edges have weight 1
                unsigned int neighborIndex = cellToIndex(neighbor);

                // If we found a shorter path to neighbor
                if (distances.find(neighborIndex) == distances.end() || 
                    newDistance < distances[neighborIndex])
                {
                    distances[neighborIndex] = newDistance;
                    _map->_grid->at(neighbor.row).at(neighbor.col).parent = current.cell;
                    priorityQueue.push({neighbor, newDistance});
                }
            }
        }
        
        // If priorityQueue is empty and we haven't found the end, no path exists
        if (priorityQueue.empty() && !isFinished)
        {
            isFinished = true;
            PLOGI << "Dijkstra pathfinding completed - no path found";
        }

        _stepCounter++;
    }

    void DijkstraFinding::markVisited(Cell cell)
    {
        _map->setVisitedTile(cell);
    }

    void DijkstraFinding::constructPath()
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
                PLOGE << "Dijkstra path reconstruction failed: invalid parent chain";
                return;
            }
            
            current = parent;
            iterations++;
        }
        
        if (iterations >= maxIterations) {
            PLOGE << "Dijkstra path reconstruction failed: maximum iterations reached";
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
        PLOGI << "Dijkstra path constructed successfully with " << path.size() << " cells";
    }

    unsigned int DijkstraFinding::cellToIndex(Cell cell)
    {
        return cell.row * _map->_grid->at(0).size() + cell.col;
    }
}
