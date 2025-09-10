//
// Created by Lucas Heinschke on 10.09.25.
//

#include "PathfindingFactory.h"
#include "plog/Log.h"

namespace path
{
    std::unique_ptr<Pathfinding> PathfindingFactory::createPathfinder(PathfindingAlgorithm algorithm, GridMap* map)
    {
        switch (algorithm)
        {
            case PathfindingAlgorithm::BFS:
                return std::make_unique<BFSFinding>(map);
                
            case PathfindingAlgorithm::DFS:
                return std::make_unique<DFSFinding>(map);
                
            case PathfindingAlgorithm::DIJKSTRA:
                return std::make_unique<DijkstraFinding>(map);
                
            case PathfindingAlgorithm::ASTAR:
                return std::make_unique<AStarFinding>(map);
                
            default:
                return std::make_unique<BFSFinding>(map);
        }
    }

    std::string PathfindingFactory::getAlgorithmName(PathfindingAlgorithm algorithm)
    {
        switch (algorithm)
        {
            case PathfindingAlgorithm::BFS:      return "Breadth-First Search (BFS)";
            case PathfindingAlgorithm::DFS:      return "Depth-First Search (DFS)";
            case PathfindingAlgorithm::DIJKSTRA: return "Dijkstra's Algorithm";
            case PathfindingAlgorithm::ASTAR:    return "A* Algorithm";
            default:                             return "Unknown Algorithm";
        }
    }

    PathfindingAlgorithm PathfindingFactory::getNextAlgorithm(PathfindingAlgorithm current)
    {
        switch (current)
        {
            case PathfindingAlgorithm::BFS:      return PathfindingAlgorithm::DFS;
            case PathfindingAlgorithm::DFS:      return PathfindingAlgorithm::DIJKSTRA;
            case PathfindingAlgorithm::DIJKSTRA: return PathfindingAlgorithm::ASTAR;
            case PathfindingAlgorithm::ASTAR:    return PathfindingAlgorithm::BFS;
            default:                             return PathfindingAlgorithm::BFS;
        }
    }
}
