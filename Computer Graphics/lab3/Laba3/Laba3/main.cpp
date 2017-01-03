#include <SFML/Graphics.hpp>

// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"
#include "SierpinskiTile.cpp"

const int SCR_W = 640;
const int SCR_H = 480;
const int TILE_W = 5; //Each tile's width
const int TILE_H = 5; //Each tile's height

int main(int, char const**) {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    
    SierpinskiTile *tile = new SierpinskiTile(SCR_W, SCR_H, TILE_W, TILE_H);
    tile->setTile((SCR_W / TILE_W) / 2, 0);
    
    int row = 0;
    
    // Start the game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window : exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Espace pressed : exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        // Clear screen
        window.clear();
        
        if (row < SCR_H / TILE_H) {
            tile->draw(window, 0, 255, 0, row - 1);
            window.display();
            tile->calculate(row++);
        }

        // Update the window
        window.display();
    }
    
    delete tile;
    
    return EXIT_SUCCESS;
}
