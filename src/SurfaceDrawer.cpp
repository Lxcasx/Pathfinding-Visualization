//
// Created by lucas on 29.01.24.
//

#include "SurfaceDrawer.h"
#include "DEFINITIONS.h"
#include <utility>
#include <iostream>

SurfaceDrawer::SurfaceDrawer(GameDataRef data, GridRef grid) : _data(std::move(data)), _grid(std::move(grid)) {}

void SurfaceDrawer::draw(float dt) {
    if (this->_data == nullptr) {
        return;
    }

    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            CellField cell = _grid->at(i).at(j);

            switch (cell.state) {
                case CellState::WALL:
                    cellShape.setFillColor(COLOR_WALL);
                    break;
                case CellState::START:
                    cellShape.setFillColor(COLOR_START);
                    break;
                case CellState::END:
                    cellShape.setFillColor(COLOR_END);
                    break;
                case CellState::PATH:
                    cellShape.setFillColor(COLOR_PATH);
                    break;
                default:
                    if (cell.visited) {
                        cellShape.setFillColor(COLOR_VISITED);
                    } else {
                        cellShape.setFillColor(COLOR_BG);
                    }
            }

            float x = i * _size;
            float y = j * _size;

            if (cell.state == CellState::PATH) {
                std::cout << "" << std::endl;
            }

            cellShape.setPosition(x, y);
            this->_data->window.draw(cellShape);
        }
    }
}

void SurfaceDrawer::setSize(int rows, int cols, int size) {
    _rows = rows;
    _cols = cols;
    _size = size;

    cellShape = sf::RectangleShape(sf::Vector2f(_size, _size));
}