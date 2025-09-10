//
// Created by Lucas Heinschke on 10.09.25.
//

#ifndef PATHFINDING_ASTARFINDING_H
#define PATHFINDING_ASTARFINDING_H

#include "../Grid.h"
#include "Pathfinding.h"
#include "SFML/Graphics.hpp"
#include <queue>
#include <unordered_map>
#include <functional>

namespace path
{
    struct AStarNode {
        Cell cell;
        float fCost;
        float gCost;
        float hCost;
        
        bool operator>(const AStarNode& other) const {
            return fCost > other.fCost;
        }
    };

    class AStarFinding : public Pathfinding
    {
    public:
        AStarFinding(GridMap *map);
        void setStart(Cell start) override;
        void setEnd(Cell start) override;
        void clear() override;
        void nextStep() override;
        void constructPath() override;

    private:
        std::priority_queue<AStarNode, std::vector<AStarNode>, std::greater<AStarNode>> openSet;
        std::unordered_map<unsigned int, float> gScores;
        std::unordered_map<unsigned int, float> fScores;
        int _stepCounter;
        int _batchSize;

        float heuristic(Cell a, Cell b);
        unsigned int cellToIndex(Cell cell);
        void markVisited(Cell cell);
    };
}

#endif // PATHFINDING_ASTARFINDING_H
