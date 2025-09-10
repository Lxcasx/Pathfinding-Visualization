//
// Created by Lucas Heinschke on 10.09.25.
//

#ifndef PATHFINDING_DIJKSTRAFINDING_H
#define PATHFINDING_DIJKSTRAFINDING_H

#include "../Grid.h"
#include "Pathfinding.h"
#include "SFML/Graphics.hpp"
#include <queue>
#include <unordered_map>

namespace path
{
    struct DijkstraNode {
        Cell cell;
        float distance;
        
        bool operator>(const DijkstraNode& other) const {
            return distance > other.distance;
        }
    };

    class DijkstraFinding : public Pathfinding
    {
    public:
        DijkstraFinding(GridMap *map);
        void setStart(Cell start) override;
        void setEnd(Cell start) override;
        void clear() override;
        void nextStep() override;
        void constructPath() override;

    private:
        std::priority_queue<DijkstraNode, std::vector<DijkstraNode>, std::greater<DijkstraNode>> priorityQueue;
        std::unordered_map<unsigned int, float> distances;
        int _stepCounter;
        int _batchSize;

        unsigned int cellToIndex(Cell cell);
        void markVisited(Cell cell);
    };
}

#endif // PATHFINDING_DIJKSTRAFINDING_H
