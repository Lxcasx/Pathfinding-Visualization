//
// Created by lucas on 27.01.24.
//

#ifndef PATHFINDING_DEFINITIONS_H
#define PATHFINDING_DEFINITIONS_H

constexpr unsigned int WINDOW_WIDTH = 1280;
constexpr unsigned int WINDOW_HEIGHT = 800;
constexpr float GRID_SIZE = 16.f;

#define WINDOW_TITLE "Pathfinding Visualization"

#define SPLASH_STATE_SHOW_TIME 3.0
#define SPLASH_STATE_BACKGROUND_FILEPATH "./resources/res/images/splash_state_background.png"

#define MAIN_STATE_BACKGROUND_FILEPATH "./resources/res/images/main_state_background.png"
#define MAIN_STATE_START_BUTTON_FILEPATH "./resources/res/images/main_state_start_button.png"
#define MAIN_STATE_INFO_BUTTON_FILEPATH "./resources/res/images/main_state_info_button.png"

#define GAME_STATE_WALL_SOUND_FILEPATH "./resources/res/sounds/wall_click.wav"


const sf::Color COLOR_START(0, 255, 94, 255);
const sf::Color COLOR_END(255, 74, 54, 255);
const sf::Color COLOR_BG(28, 28, 28, 255);
const sf::Color COLOR_WALL(250, 250, 250, 255);
const sf::Color COLOR_VISITED(66, 135, 245, 255);
const sf::Color COLOR_PATH(255, 230, 69, 255);

#endif //PATHFINDING_DEFINITIONS_H
