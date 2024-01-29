//
// Created by lucas on 27.01.24.
//

#ifndef PATHFINDING_SPLASHSTATE_H
#define PATHFINDING_SPLASHSTATE_H

#include "../engine/State.h"
#include "../Game.h"


class SplashState : public engine::State {
public:
    SplashState(GameDataRef data);

    void init();

    void handleInput();

    void update(float dt);

    void draw(float dt);

private:
    GameDataRef _data;
    sf::Clock _clock;
    sf::Sprite _background;
};


#endif //PATHFINDING_SPLASHSTATE_H
