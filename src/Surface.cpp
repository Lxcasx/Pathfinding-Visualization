//
// Created by lucas on 29.01.24.
//

#include "Surface.h"
#include "pathfinding/PathfindingFactory.h"
#include "plog/Log.h"
#include "DEFINITIONS.h"
#include <cmath>
#include <chrono>
#include <utility>

Surface::Surface(GameDataRef data) : _data(std::move(data)), _grid(&_gridData), _map(_grid), _currentAlgorithm(PathfindingAlgorithm::BFS)
{
    _pathfinder = path::PathfindingFactory::createPathfinder(_currentAlgorithm, &_map);
}

void Surface::prepare()
{
    for (int i = 0; i < rows; i++)
    {
        std::vector<CellField> row;

        for (int j = 0; j < cols; j++)
        {
            if (j == 0 || j == cols - 1 || i == 0 || i == rows - 1)
                row.push_back(CellField{CellState::WALL});
            else
                row.push_back(CellField{CellState::EMPTY});
        }

        _grid->push_back(row);
    }

    level.resize(_width * _height);
    _map.load(sf::Vector2u(GRID_SIZE, GRID_SIZE), _width, _height);
}

void Surface::init(int width, int height)
{
    _width = width;
    _height = height;

    rows = std::round(_width / GRID_SIZE);
    cols = std::round(_height / GRID_SIZE);

    prepare();
}

void Surface::setPosition(float x, float y)
{
}

void Surface::draw(float dt)
{
    // Only update if there are dirty tiles to flush
    if (!_map.getDirtyTiles().empty()) {
        _map.flushDirtyTiles();
    }
    
    _data->window.draw(_map);

    if (startPos != Cell{-1, -1} && endPos != Cell{-1, -1} && !_pathfinder->isFinished)
    {
        _pathfinder->nextStep();
        // Note: Individual tiles are marked dirty in the pathfinding algorithm
    }

    if (startPos != Cell{-1, -1} && endPos != Cell{-1, -1} && _pathfinder->isFinished && !_pathfinder->pathConstructed)
    {
        _pathfinder->constructPath();
        // Immediately flush all dirty tiles for complete path visualization
        _map.flushDirtyTilesImmediate();
    }
}

void Surface::update(float dt)
{
}

void Surface::setWall(sf::Vector2i pos)
{
    Cell cell{};

    if (!isPositionInGrid(pos, &cell))
    {
        return;
    }

    setWall(cell);
}

void Surface::setWall(Cell pos)
{
    if (lastPos != Cell{-1, -1})
    {
        correctWall(pos, lastPos);
    }

    lastPos = pos;
    setCellField(pos, CellState::WALL);
}

bool Surface::isPositionInGrid(sf::Vector2i pos, Cell *cell) const
{
    // Optimized bounds checking with early return
    if (pos.x < 0 || pos.y < 0) return false;
    
    int row = pos.x / GRID_SIZE;
    int col = pos.y / GRID_SIZE;

    if (row >= rows || col >= cols) return false;

    cell->row = row;
    cell->col = col;

    return true;
}

// Correct the placement of walls that were not captured by the loop using the bresenham line algorithm.
void Surface::correctWall(Cell start, Cell end)
{
    int x1 = start.row;
    int y1 = start.col;
    int x2 = end.row;
    int y2 = end.col;

    int dx = std::abs(x2 - x1);
    int dy = std::abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while (true)
    {
        setCellField(Cell{x1, y1}, CellState::WALL);

        if (x1 == x2 && y1 == y2)
        {
            break;
        }

        int e2 = 2 * err;

        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

void Surface::handleInput()
{
    // draw wall
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
    {
        setWall(sf::Mouse::getPosition(_data->window));
    }
    // draw start
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        setStart(sf::Mouse::getPosition(_data->window));
    }
    // draw end
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
    {
        setEnd(sf::Mouse::getPosition(_data->window));
    }
    else
    {
        lastPos = Cell{-1, -1};
    }
}

void Surface::clear()
{
    _grid->clear();
    prepare();
    _pathfinder->clear();
    startPos = Cell{-1, -1};
    endPos = Cell{-1, -1};
    _map.setFullUpdateNeeded();
}

void Surface::setStart(sf::Vector2i pos)
{
    if (_pathfinder->isFinished)
        return;

    Cell cell{};

    if (!isPositionInGrid(pos, &cell))
    {
        return;
    }

    setStart(cell);
}

void Surface::setStart(Cell cell)
{
    CellField field = _grid->at(cell.row).at(cell.col);

    if (field.state == CellState::WALL || field.state == CellState::END)
        return;

    // delete old start position
    if (startPos != Cell{-1, -1})
    {
        setCellField(startPos, CellState::EMPTY);
    }

    startPos = cell;
    _pathfinder->setStart(startPos);

    setCellField(cell, CellState::START);
}

void Surface::setEnd(sf::Vector2i pos)
{
    if (_pathfinder->isFinished)
        return;

    Cell cell{};

    if (!isPositionInGrid(pos, &cell))
    {
        return;
    }

    setEnd(cell);
}

void Surface::setEnd(Cell cell)
{
    CellField field = _grid->at(cell.row).at(cell.col);

    if (field.state == CellState::WALL || field.state == CellState::START)
        return;

    // delete old start position
    if (endPos != Cell{-1, -1})
    {
        setCellField(endPos, CellState::EMPTY);
    }

    endPos = cell;
    _pathfinder->setEnd(endPos);

    setCellField(cell, CellState::END);
}

void Surface::save()
{
}

void Surface::setCellField(Cell cell, CellState state)
{
    _map.setTile(cell, state);
}

void Surface::switchAlgorithm()
{
    // Get the next algorithm
    PathfindingAlgorithm oldAlgorithm = _currentAlgorithm;
    _currentAlgorithm = path::PathfindingFactory::getNextAlgorithm(_currentAlgorithm);
    
    // Create new pathfinder
    try {
        _pathfinder = path::PathfindingFactory::createPathfinder(_currentAlgorithm, &_map);
    } catch (const std::exception& e) {
        PLOGE << "Failed to create pathfinder: " << e.what();
        // Fallback to BFS if creation fails
        _currentAlgorithm = PathfindingAlgorithm::BFS;
        _pathfinder = path::PathfindingFactory::createPathfinder(_currentAlgorithm, &_map);
    }
    
    // Clear the grid and reset start/end positions
    clear();
}

std::string Surface::getCurrentAlgorithmName() const
{
    return path::PathfindingFactory::getAlgorithmName(_currentAlgorithm);
}