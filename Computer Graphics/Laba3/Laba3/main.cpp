#include <iostream>
#include "fill_algorithms.hpp"

int main() {
    std::vector<sf::Vector2i> vertex;
    sf::RenderWindow window(sf::VideoMode(width, height), "lab3");
    sf::Vector2i min, max;
    window.clear();
    sf::Event event;
    sf::RectangleShape node(sf::Vector2f(4, 4));
    sf::Image screen;
    screen.create(width, height);
    node.setFillColor(sf::Color(150, 15, 200));
    
    
    while (window.isOpen()) {
        
        while (window.pollEvent(event))
            
        if (event.type == sf::Event::Closed)
                window.close();
        
        if (event.type == sf::Event::MouseMoved and sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            draw_point(screen, event.mouseMove.x, event.mouseMove.y, 10);
            draw_img(window, screen);
        }
        
        if (event.type == sf::Event::MouseButtonPressed and sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
            if (vertex.empty())
                vertex.push_back(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
            else {
                if (sf::Vector2i(event.mouseButton.x, event.mouseButton.y) != vertex.back())
                    vertex.push_back(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
            }
            draw_point(screen, event.mouseButton.x, event.mouseButton.y, 0);
            draw_img(window, screen);
            window.display();
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            if (!vertex.empty())
                draw_polygon(window, screen, vertex);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
            window.clear();
        
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left)
                flood_fill(window, screen, sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
            min = vertex[0];
            max = min;
            
            std::vector<sf::Vector2i>::iterator it = vertex.begin();
            for (; it != vertex.end(); ++it) {
                if (min.x > it->x)
                    min.x = it->x;
                
                if (min.y > it->y)
                    min.y = it->y;
                
                if (max.x < it->x)
                    max.x = it->x;
                
                if (max.y < it->y)
                    max.y = it->y;
            }
            //screen.create(width, height);
            scan_line(window, screen, vertex, max, min);
            // xor_fill(window, screen, vertex, max, min);
            vertex.clear();
        }
        window.display();
    }
    return 0;
}
