//
// Created by lucas on 29.01.24.
//

#ifndef PATHFINDING_MAINSTATE_H
#define PATHFINDING_MAINSTATE_H

#include "../engine/State.h"
#include "../Game.h"
#include "../ui/UIManager.h"
#include "../ui/Button.h"
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

    // UI Components
    ui::UIManager _uiManager;
    std::shared_ptr<ui::Button> _startButton;
    std::shared_ptr<ui::Button> _infoButton;
    std::shared_ptr<ui::Button> _exitButton;

    void loadAssets();
    void initSprites();
    void setupUI();
};

#endif // PATHFINDING_MAINSTATE_H
