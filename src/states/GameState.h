//
// Created by lucas on 29.01.24.
//

#ifndef PATHFINDING_GAMESTATE_H
#define PATHFINDING_GAMESTATE_H

#include "../engine/State.h"
#include "../Game.h"
#include "../Surface.h"

class GameState : public engine::State
{
public:
    GameState(GameDataRef data);

    void init();

    void handleInput();

    void update(float dt);

    void draw(float dt);

private:
    GameDataRef _data;
    Surface _surface = Surface(_data);

    void loadAssets();
    void initSprites();
};

#endif // PATHFINDING_GAMESTATE_H
