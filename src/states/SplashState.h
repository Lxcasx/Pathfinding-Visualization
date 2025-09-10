//
// Created by lucas on 27.01.24.
//

#ifndef PATHFINDING_SPLASHSTATE_H
#define PATHFINDING_SPLASHSTATE_H

#include "../engine/State.h"
#include "../Game.h"
#include <optional>

class SplashState : public engine::State
{
public:
    SplashState(GameDataRef data);

    void init();

    void handleInput();

    void update(float dt);

    void draw(float dt);

private:
    GameDataRef _data;
    sf::Clock _clock;
    std::optional<sf::Sprite> _background;

    void loadAssets();
    void initSprites();
};

#endif // PATHFINDING_SPLASHSTATE_H
