//
// Created by lucas on 27.01.24.
//

#ifndef PATHFINDING_GAME_H
#define PATHFINDING_GAME_H

#include "SFML/Graphics.hpp"
#include "engine/StateMachine.h"
#include "engine/AssetManager.h"
#include "engine/InputManager.h"

struct GameData {
    engine::StateMachine machine;
    engine::AssetManager assets;
    engine::InputManager input;
    sf::RenderWindow window;
};

typedef std::shared_ptr<GameData> GameDataRef;

class Game {
public:
    Game(int width, int height, const std::string &title);

private:
    const float dt = 1.0f / 60.0f;
    sf::Clock _clock;

    GameDataRef _data = std::make_shared<GameData>();

    void run();
};


#endif //PATHFINDING_GAME_H
