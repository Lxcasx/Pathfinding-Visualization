# Simple UI for visualizing pathfinding algorithm

> This project is a simple user interface for visualizing pathfinding algorithms. Currently, it only implements the Breadth-First Search (BFS) algorithm. The application allows users to interactively set start and end points, draw walls, and clear the grid. The BFS algorithm then finds the shortest path from the start point to the end point, navigating around the walls. The project uses the SFML multimedia library for the graphical interface, PLOG for logging, and a game engine based on a YouTube tutorial.

## How to use

1. Starting the Application: After installing the application, open it. You should see a grid displayed on the screen.

2. Drawing Walls: To draw walls, hold down the left shift key and click with the left mouse button on the cells where you want the walls to be. These cells will change color to indicate that they are walls.

3. Setting the Start Point: To set the start point, simply click on a cell in the grid with the left mouse button. The selected cell will change color to indicate that it is the start point.

4. Setting the End Point: To set the end point, click on a different cell with the right mouse button. This cell will also change color to indicate that it is the end point.

5. Running the Pathfinding Algorithm: After setting the start point, end point the algorithm will find the shortest path from the start point to the end point, navigating around the walls. The path will be displayed on the grid.

6. Clearing the Grid: To clear the grid and start over, press the 'C' key. This will remove the start point, end point, walls, and path, returning the grid to its initial state.

Remember, the application uses the Breadth-First Search (BFS) algorithm for pathfinding. This algorithm guarantees to find the shortest path, but it may not be the fastest algorithm if the grid is large.

## Keys

| Key                                       | Function        |
| ----------------------------------------- | --------------- |
| <kbd>LShift</kbd> + <kbd>Left Mouse</kbd> | Draw a wall     |
| <kbd>Left Mouse</kbd>                     | set start point |
| <kbd>Right Mouse</kbd>                    | Set endpoint    |
| <kbd>C</kbd>                              | Clear the Grid  |


## Credits
* SFML: https://github.com/SFML/SFML
    * Multimedia Libary
* PLOG: https://github.com/SergiusTheBest/plog
    * Logging Libary
* SFML Game Engine (src/engine) based on https://www.youtube.com/watch?v=tgXEws1Ef8s&list=PLorQc--wocbdLeis03PUbSuzceAUFH4YY