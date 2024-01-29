//
// Created by lucas on 29.01.24.
//

#include <list>
#include <queue>
#include "BFSFinding.h"
#include "plog/Log.h"

namespace path {
    BFSFinding::BFSFinding(Grid *grid) : _grid(grid) {}

    void BFSFinding::setStart(sf::Vector2i start) {
        this->start = start;
        queue.push(start);
        this->markVisited(start);
    }

    void BFSFinding::setEnd(sf::Vector2i end) {
        this->end = end;
    }

    void BFSFinding::clear() {
        this->finished = false;
        this->queue = {};
    }

    void BFSFinding::nextStep() {
        std::vector<sf::Vector2i> directions = {{-1, 0},
                                                {1,  0},
                                                {0,  -1},
                                                {0,  1}}; // 4 mögliche Richtungen
        sf::Vector2i current = queue.front();
        queue.pop();

        // Überprüfen, ob der Endpunkt erreicht wurde
        if (current == end) {
            // Pfad gefunden, weitere Verarbeitung hier (z.B. speichern oder ausgeben)
            this->finished = true;
            return;
        }

        // Durchlaufe alle Nachbarn
        for (const sf::Vector2i &direction: directions) {
            sf::Vector2i neighbor = current + direction;

            // Überprüfen, ob der Nachbar innerhalb der Gittergrenzen liegt und nicht besucht wurde
            if (_grid->at(neighbor.x).at(neighbor.y).state != WALL &&
                !_grid->at(neighbor.x).at(neighbor.y).visited) {

                queue.push(neighbor);
                markVisited(neighbor);

                _grid->at(neighbor.x).at(neighbor.y).parent = current;
            }
        }
    }

    void BFSFinding::markVisited(sf::Vector2i cell) {
        this->_grid->at(cell.x).at(cell.y).visited = true;
    }

    std::vector<sf::Vector2i> BFSFinding::constructPath() {
        // Pfad extrahieren, indem der Elternzeiger zurückverfolgt wird
        std::vector<sf::Vector2i> path;
        sf::Vector2i current = end;

        while (current != start) {
            path.push_back(current);

            if (_grid->at(current.x).at(current.y).state == CellState::EMPTY) {
                _grid->at(current.x).at(current.y).state = CellState::PATH;
            }

            current = _grid->at(current.x).at(current.y).parent;
        }

        // Startpunkt hinzufügen
        path.push_back(start);

        // Pfad umdrehen, um die Reihenfolge zu korrigieren
        std::reverse(path.begin(), path.end());

        return path;
    }
}