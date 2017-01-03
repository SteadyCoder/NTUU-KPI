#include <SFML/Graphics.hpp>

#include "SierpinskiTile.hpp"
#include "sierpinski_alogrithm.hpp"
#include "Line.h"
#include "KochSnowflake.h"
#include "MandelbrotSet.h"

const int screen_width = 1200;
const int screen_height = 1000;

// Width and height for sierpinski algorithm
const int tile_width = 20;
const int tile_height = 20;

int main(int, char const**) {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "SFML window");
    window.setFramerateLimit(60);
    
    // Variables and presettings for sierpinski algorithm
    SierpinskiTile *tile = new SierpinskiTile(screen_width, screen_height, tile_width, tile_height);
    tile->setTile((screen_width / tile_width) / 2, 0);
    
    // Variables and presettings for Koch algorithm
    std::list<Line*> fractal;
    fractal.push_back(new Line(200, 150, 400, 0));
    Line *line = new Line(200, 150, 400, 60);
    line->x += cos(line->angle * M_PI/180) * line->length;
    line->y += sin(line->angle * M_PI/180) * line->length;
    line->angle -= 180;
    fractal.push_back(line);
    fractal.push_back(new Line(600, 150, 400, 120));
    KochSnowflake* koch = new KochSnowflake();
    
    // Variables and presettings for Mandelbrot algorithm
    auto mandelbrot = new MandelbrotSet(screen_width, screen_height, 500, 2, (float)-0.5, 1, -1);

    window.clear();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C) {
                window.clear();
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::K) {            
                koch->kochFractal(fractal);
                window.clear();
                for (auto it = fractal.begin(); it != fractal.end(); ++it) {
                    (*it)->drawLine(window);
                }
            }
                
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M) {
                window.clear();
                mandelbrot->calcMandelbrotFractal(window, screen_width, screen_height);
            }
                
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S) {
                window.clear();
                algorithm(screen_width, screen_height, tile_width, tile_height, window, tile, sf::Color::Yellow);
            }
        }
        
        // Update the window
        window.display();
    }
    
    for (auto it = fractal.begin(); it != fractal.end(); ++it)
        delete (*it);
    
    delete tile;
    
    return EXIT_SUCCESS;
}
