//
// Created by lucas on 29.01.24.
//

#include "SurfaceDrawer.h"
#include "DEFINITIONS.h"
#include <utility>
#include <iostream>

SurfaceDrawer::SurfaceDrawer(GameDataRef data, GridRef grid) : _data(std::move(data)), _grid(grid) {

}

void SurfaceDrawer::draw(float dt) {
    if (this->_data == nullptr) {
        return;
    }

    texture.setSmooth(true);

    texture.display();
    sf::Sprite sprite(texture.getTexture());
    _data->window.draw(sprite);

    return;


    return;
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            CellField cell = _grid->at(i).at(j);
            sf::RectangleShape shape;
/*
            switch (cell.state) {
                case CellState::WALL:
                    shape = shapes.wall;
                    break;
                case CellState::START:
                    //cellShape.setFillColor(COLOR_START);
                    break;
                case CellState::END:
                    //cellShape.setFillColor(COLOR_END);
                    break;
                case CellState::PATH:
                    //cellShape.setFillColor(COLOR_PATH);
                    break;
                default:
                    if (cell.visited) {
                        //cellShape.setFillColor(COLOR_VISITED);
                    } else {
                        //cellShape.setFillColor(COLOR_BG);
                    }
            }

            float x = i * _size;
            float y = j * _size;
            shape.setPosition(x, y);
            this->_data->window.draw(shape);*/
/*
            float x = i * _size;
            float y = j * _size;
            cellShape.setPosition(x, y);

            if (cell.state == CellState::PATH) {
                std::cout << "" << std::endl;
            }

            this->_data->window.draw(cellShape);*/
        }
    }
}

void SurfaceDrawer::setSize(int rows, int cols, int size) {
    _rows = rows;
    _cols = cols;
    _size = size;

    int width = _size * _rows;
    int height = _size * _cols;
    texture.create(width, height);
    texture.clear(COLOR_BG);

    //shapes.wall = sf::RectangleShape(sf::Vector2f(_size, _size));
}

void SurfaceDrawer::change(Cell cell, CellField field) {
    sf::VertexArray rect;
    int row = cell.row;
    int col = cell.col;

    switch (field.state) {
        case CellState::WALL:
            rect = getRect(row, col, COLOR_WALL);
            break;
        case CellState::START:
            rect = getRect(row, col, COLOR_START);
            break;
        case CellState::END:
            rect = getRect(row, col, COLOR_END);
            break;
        case CellState::PATH:
            rect = getRect(row, col, COLOR_PATH);
            break;
        default:
            if (field.visited) {
                rect = getRect(row, col, COLOR_VISITED);
            } else {
                rect = getRect(row, col, COLOR_BG);
            }
            break;
    }

    texture.draw(rect);
}

// https://www.sfml-dev.org/tutorials/2.6/graphics-vertex-array.php
sf::VertexArray SurfaceDrawer::getRect(int row, int col, sf::Color color) const {
    sf::VertexArray rect(sf::Quads, 4);

    float x1 = row * _size;
    float y1 = col * _size;

    float x2 = row * _size;
    float y2 = col * _size + _size;

    float x3 = row * _size + _size;
    float y3 = col * _size + _size;

    float x4 = row * _size + _size;
    float y4 = col * _size;

    rect[0].position = sf::Vector2f(x1, y1);
    rect[1].position = sf::Vector2f(x2, y2);
    rect[2].position = sf::Vector2f(x3, y3);
    rect[3].position = sf::Vector2f(x4, y4);

    rect[0].color = color;
    rect[1].color = color;
    rect[2].color = color;
    rect[3].color = color;

    return rect;
}