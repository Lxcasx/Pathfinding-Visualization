// Default font data - a minimal embedded font for demo purposes
// In a real project, you should load a proper .ttf font file
// This is just for demonstration to make text buttons work

#ifndef PATHFINDING_DEFAULT_FONT_H
#define PATHFINDING_DEFAULT_FONT_H

#include <SFML/Graphics.hpp>

namespace ui {
    // Helper function to get a default font
    // In a real project, you should load a proper font file
    inline sf::Font& getDefaultFont() {
        static sf::Font defaultFont;
        static bool fontLoaded = false;
        
        if (!fontLoaded) {
            // Try to load a system font, fallback to default if not found
            // On Linux, try common system font paths
            const std::vector<std::string> fontPaths = {
                "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
                "/usr/share/fonts/TTF/arial.ttf",
                "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
                "/System/Library/Fonts/Arial.ttf", // macOS
                "C:/Windows/Fonts/arial.ttf" // Windows
            };
            
            for (const auto& path : fontPaths) {
                if (defaultFont.loadFromFile(path)) {
                    fontLoaded = true;
                    break;
                }
            }
            
            // If no system font found, the font will be empty
            // SFML will use its internal default font
        }
        
        return defaultFont;
    }
}

#endif // PATHFINDING_DEFAULT_FONT_H
