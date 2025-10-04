# UI Module

This module provides reusable UI components for the Pathfinding Visualization project.

## Components

### Button

A versatile button component that supports both texture-based and text-based buttons.

#### Features

- **Two Button Types:**
  - Texture-based buttons (using existing sprite textures)
  - Text-based buttons (with customizable background and text)

- **Interactive States:**
  - Normal (default state)
  - Hovered (mouse over)
  - Pressed (mouse down)
  - Disabled (non-interactive)

- **Customization:**
  - Custom colors for each state
  - Custom text colors for each state
  - Configurable size and position
  - Click callbacks
  - Enable/disable functionality

#### Usage Examples

##### Text-based Button

```cpp
#include "ui/Button.h"
#include "ui/UIManager.h"

// Load a font first
_data->assets.loadFont("button_font", "./resources/res/fonts/arial.ttf");
sf::Font& font = _data->assets.getFont("button_font");

// Create a text button
auto button = std::make_shared<ui::Button>(
    font, 
    "Click Me!", 
    sf::Vector2f(100, 200),  // position
    sf::Vector2f(150, 40)    // size
);

// Set click callback
button->setOnClickCallback([]() {
    std::cout << "Button clicked!" << std::endl;
});

// Customize colors (optional)
button->setColors(
    sf::Color(70, 130, 180),   // Normal
    sf::Color(100, 149, 237),  // Hovered
    sf::Color(50, 100, 150),   // Pressed
    sf::Color(100, 100, 100)   // Disabled
);
```

##### Texture-based Button

```cpp
// Load texture first
_data->assets.loadTexture("start_button", "./resources/res/images/start_button.png");
sf::Texture& texture = _data->assets.getTexture("start_button");

// Create texture button
auto button = std::make_shared<ui::Button>(
    texture,
    sf::Vector2f(100, 200)  // position
);

// Set click callback
button->setOnClickCallback([]() {
    std::cout << "Start button clicked!" << std::endl;
});
```

### UIManager

A manager class to handle multiple UI elements efficiently.

#### Features

- Manages multiple buttons
- Handles mouse input for all buttons
- Renders all UI elements
- Easy addition/removal of buttons

#### Usage

```cpp
#include "ui/UIManager.h"

// Create UI manager
ui::UIManager uiManager;

// Add buttons
uiManager.addButton(button1);
uiManager.addButton(button2);

// In your update loop
uiManager.update(_data->window);

// In your draw loop
uiManager.draw(_data->window);
```

## Integration with Existing States

To use the UI components in your existing states:

1. Include the UI headers:
```cpp
#include "ui/UIManager.h"
#include "ui/Button.h"
```

2. Add UI manager as a member variable:
```cpp
private:
    ui::UIManager _uiManager;
    std::shared_ptr<ui::Button> _myButton;
```

3. Setup UI in your init() method:
```cpp
void MyState::init()
{
    // Load font
    _data->assets.loadFont("ui_font", "./resources/res/fonts/arial.ttf");
    sf::Font& font = _data->assets.getFont("ui_font");
    
    // Create button
    _myButton = std::make_shared<ui::Button>(
        font, "My Button", sf::Vector2f(100, 100)
    );
    _myButton->setOnClickCallback([this]() {
        // Handle button click
    });
    
    _uiManager.addButton(_myButton);
}
```

4. Update and draw in your methods:
```cpp
void MyState::update(float dt)
{
    _uiManager.update(_data->window);
}

void MyState::draw(float dt)
{
    _data->window.clear();
    
    // Draw your other content here
    
    _uiManager.draw(_data->window);
    _data->window.display();
}
```

## File Structure

```
src/ui/
├── Button.h              # Button class declaration
├── Button.cpp            # Button class implementation
├── UIManager.h           # UI manager class declaration
├── UIManager.cpp         # UI manager class implementation
├── ExampleUIState.h      # Example state using UI components
├── ExampleUIState.cpp    # Example state implementation
└── README.md            # This file
```

## Building

Make sure to include the UI source files in your CMakeLists.txt:

```cmake
# Add to your source files
set(SOURCES
    # ... existing sources ...
    src/ui/Button.cpp
    src/ui/UIManager.cpp
    # Add ExampleUIState.cpp if you want to use the example
)
```

## Important Notes

- **Font Loading**: For text-based buttons to display text properly, you must load a font first using the AssetManager
- **SFML 3.0 Compatibility**: This UI module is designed for SFML 3.0+ and uses modern SFML API
- Always load fonts before creating text-based buttons
- The example state (`ExampleUIState`) demonstrates proper usage but requires font loading for text display
- UI elements are drawn in the order they were added to the UIManager
- Button states are automatically managed based on mouse interaction

## Font Loading Example

Before creating text-based buttons, load a font:

```cpp
// In your state's init() method
_data->assets.loadFont("ui_font", "./path/to/your/font.ttf");
const sf::Font& font = _data->assets.getFont("ui_font");

// Now you can create text-based buttons
auto button = std::make_shared<ui::Button>(
    font, "Button Text", sf::Vector2f(100, 100)
);
```

If you don't have a font file, you can download a free font like:
- [Roboto](https://fonts.google.com/specimen/Roboto)
- [Open Sans](https://fonts.google.com/specimen/Open+Sans)
- Or use system fonts (location varies by OS)
