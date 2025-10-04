# UI Button Integration Example

Here's a simple example showing how to integrate a UI button into the existing MainState:

## Step 1: Add UI includes to MainState.h

```cpp
#include "../ui/UIManager.h"
#include "../ui/Button.h"
```

## Step 2: Add UI members to MainState class

```cpp
private:
    // ... existing members ...
    ui::UIManager _uiManager;
    std::shared_ptr<ui::Button> _resetButton;
```

## Step 3: Setup UI in MainState::init()

```cpp
void MainState::init()
{
    PLOGI << "Initializing main state";

    loadAssets();
    initSprites();
    
    // Setup UI - Load a font if you have one
    // _data->assets.loadFont("ui_font", "./resources/res/fonts/arial.ttf");
    // const sf::Font& font = _data->assets.getFont("ui_font");
    
    // For this example, using texture-based button with existing assets
    // You can also create text-based buttons if you have a font loaded
    
    // Create a simple reset button (example with solid color background)
    sf::Font defaultFont; // Note: Won't show text without proper font
    _resetButton = std::make_shared<ui::Button>(
        defaultFont,
        "Reset",
        sf::Vector2f(50, WINDOW_HEIGHT - 100), // Bottom-left corner
        sf::Vector2f(120, 40)
    );
    
    _resetButton->setOnClickCallback([this]() {
        PLOGI << "Reset button clicked!";
        // Add your reset logic here
    });
    
    _resetButton->setColors(
        sf::Color(60, 60, 60),     // Normal - Dark gray
        sf::Color(80, 80, 80),     // Hovered - Lighter gray
        sf::Color(40, 40, 40),     // Pressed - Darker gray
        sf::Color(30, 30, 30)      // Disabled - Very dark
    );
    
    _uiManager.addButton(_resetButton);
}
```

## Step 4: Update MainState::update()

```cpp
void MainState::update(float dt)
{
    // ... existing update code ...
    
    // Update UI
    _uiManager.update(_data->window);
}
```

## Step 5: Update MainState::draw()

```cpp
void MainState::draw(float dt)
{
    _data->window.clear();

    // Draw background
    if (_background)
    {
        _data->window.draw(*_background);
    }

    // Draw existing buttons
    if (_startButton)
    {
        _data->window.draw(*_startButton);
    }

    if (_infoButton)
    {
        _data->window.draw(*_infoButton);
    }
    
    // Draw UI elements
    _uiManager.draw(_data->window);

    _data->window.display();
}
```

## Alternative: Using Texture-based Buttons

If you want to use the existing button textures instead of text-based buttons:

```cpp
void MainState::init()
{
    // ... existing code ...
    
    // Create texture-based button using existing assets
    if (_data->assets.getTexture("start_button_texture")) // If this texture exists
    {
        auto textureButton = std::make_shared<ui::Button>(
            _data->assets.getTexture("start_button_texture"),
            sf::Vector2f(100, 400)
        );
        
        textureButton->setOnClickCallback([this]() {
            PLOGI << "Texture button clicked!";
        });
        
        _uiManager.addButton(textureButton);
    }
}
```

This approach allows you to:
- Keep your existing sprite-based buttons
- Add modern UI buttons alongside them
- Have consistent button behavior with callbacks
- Easy state management for buttons (hover, pressed, disabled)

The UI system is designed to coexist with your existing SFML sprites and drawing code.
