//
// Created by lucas on 29.01.24.
//

#ifndef PATHFINDING_MAINSTATE_H
#define PATHFINDING_MAINSTATE_H

#include "../engine/State.h"
#include "../Game.h"
#include <optional>

class MainState : public engine::State
{
public:
    MainState(GameDataRef data);

    void init();

    void handleInput();

    void update(float dt);

    void draw(float dt);

private:
    GameDataRef _data;
    std::optional<sf::Sprite> _background;
    std::optional<sf::Sprite> _startButton;
    std::optional<sf::Sprite> _infoButton;

    void loadAssets();
    void initSprites();
};

#endif // PATHFINDING_MAINSTATE_H
