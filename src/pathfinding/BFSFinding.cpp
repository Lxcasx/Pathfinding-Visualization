//
// Created by lucas on 29.01.24.
//

#include <list>
#include <queue>
#include <utility>
#include "BFSFinding.h"
#include "plog/Log.h"

namespace path {
    BFSFinding::BFSFinding(GridRef grid) : _grid(std::move(grid)) {}

    void BFSFinding::setStart(Cell start) {
        this->start = start;
        queue.push(start);
        this->markVisited(start);
    }

    void BFSFinding::setEnd(Cell end) {
        this->end = end;
    }

    void BFSFinding::clear() {
        this->finished = false;
        this->queue = {};
    }

    void BFSFinding::nextStep() {
        std::vector<Cell> directions = {{-1, 0},
                                        {1,  0},
                                        {0,  -1},
                                        {0,  1}}; // 4 mögliche Richtungen
        Cell current = queue.front();
        queue.pop();

        // Überprüfen, ob der Endpunkt erreicht wurde
        if (current == end) {
            // Pfad gefunden, weitere Verarbeitung hier (z.B. speichern oder ausgeben)
            this->finished = true;
            return;
        }

        // Durchlaufe alle Nachbarn
        for (const Cell &direction: directions) {
            Cell neighbor = current + direction;

            // Überprüfen, ob der Nachbar innerhalb der Gittergrenzen liegt und nicht besucht wurde
            if (_grid->at(neighbor.row).at(neighbor.col).state != WALL &&
                !_grid->at(neighbor.row).at(neighbor.col).visited) {

                queue.push(neighbor);
                markVisited(neighbor);

                _grid->at(neighbor.row).at(neighbor.col).parent = current;
            }
        }
    }

    void BFSFinding::markVisited(Cell cell) {
        this->_grid->at(cell.row).at(cell.col).visited = true;
    }

    std::vector<Cell> BFSFinding::constructPath() {
        // Pfad extrahieren, indem der Elternzeiger zurückverfolgt wird
        std::vector<Cell> path;
        Cell current = end;

        while (current != start) {
            path.push_back(current);

            current = _grid->at(current.row).at(current.col).parent;
        }

        // Startpunkt hinzufügen
        path.push_back(start);

        // Pfad umdrehen, um die Reihenfolge zu korrigieren
        std::reverse(path.begin(), path.end());

        for (int i = 0; i < size(path); ++i) {
            current = path[i];
            if (_grid->at(current.row).at(current.col).state != CellState::END) {
                _grid->at(current.row).at(current.col).state = CellState::PATH;
            }
        }

        return path;
    }
}