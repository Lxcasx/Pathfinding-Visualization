//
// Created by lucas on 10.09.25.
//

#ifndef PATHFINDING_EXAMPLE_UI_STATE_H
#define PATHFINDING_EXAMPLE_UI_STATE_H

#include "../engine/State.h"
#include "../Game.h"
#include "../ui/UIManager.h"
#include "../ui/Button.h"
#include <memory>

class ExampleUIState : public engine::State
{
public:
    ExampleUIState(GameDataRef data);

    void init() override;
    void handleInput() override;
    void update(float dt) override;
    void draw(float dt) override;

private:
    void loadAssets() override;
    void initSprites() override;
    
    GameDataRef _data;
    ui::UIManager _uiManager;
    
    std::shared_ptr<ui::Button> _startButton;
    std::shared_ptr<ui::Button> _exitButton;
    std::shared_ptr<ui::Button> _settingsButton;

    void setupUI();
    void onStartButtonClicked();
    void onExitButtonClicked();
    void onSettingsButtonClicked();
};

#endif // PATHFINDING_EXAMPLE_UI_STATE_H
