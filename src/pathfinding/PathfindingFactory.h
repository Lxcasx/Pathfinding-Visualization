//
// Created by Lucas Heinschke on 10.09.25.
//

#ifndef PATHFINDING_PATHFINDINGFACTORY_H
#define PATHFINDING_PATHFINDINGFACTORY_H

#include "../DEFINITIONS.h"
#include "Pathfinding.h"
#include "BFSFinding.h"
#include "DFSFinding.h"
#include "DijkstraFinding.h"
#include "AStarFinding.h"
#include <memory>
#include <string>

namespace path
{
    class PathfindingFactory
    {
    public:
        static std::unique_ptr<Pathfinding> createPathfinder(PathfindingAlgorithm algorithm, GridMap* map);
        static std::string getAlgorithmName(PathfindingAlgorithm algorithm);
        static PathfindingAlgorithm getNextAlgorithm(PathfindingAlgorithm current);
    };
}

#endif // PATHFINDING_PATHFINDINGFACTORY_H
