//
// Created by lucas on 29.01.24.
//

#ifndef PATHFINDING_GAMESTATE_H
#define PATHFINDING_GAMESTATE_H

#include "../engine/State.h"
#include "../Game.h"
#include "../Surface.h"
#include <optional>

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
    std::optional<sf::Font> _font;
    std::optional<sf::Text> _algorithmText;
    std::optional<sf::Text> _instructionsText;

    void loadAssets();
    void initSprites();
    void updateTexts();
};

#endif // PATHFINDING_GAMESTATE_H
