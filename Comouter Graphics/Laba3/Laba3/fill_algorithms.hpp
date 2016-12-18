//
// Created by vpodilnyk on 21.11.16.
//

#ifndef GRAPHICS3_FILL_ALGORITHMS_H
#define GRAPHICS3_FILL_ALGORITHMS_H

#endif //GRAPHICS3_FILL_ALGORITHMS_H

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System.hpp>
#include <thread>
#include <math.h>
#include <mutex>
#include <vector>
#include <algorithm>
#include <stack>
#include <GLUT/glut.h>
#include <iostream>

const int height(500);
const int width(500);

bool is_vertex(std::vector<sf::Vector2i> vect, sf::Vector2i point);
bool check_range(sf::Vector2i point);
void draw_point(sf::Image &screen, int x, int y, int size);
void draw_img(sf::RenderWindow &window, sf::Image &screen);
void flood_fill(sf::RenderWindow &window, sf::Image &screen, sf::Vector2i point);
void bresenham_line(sf::RenderWindow &window, sf::Image &screen, sf::Vector2i first, sf::Vector2i second);
void scan_line(sf::RenderWindow &window, sf::Image &screen, std::vector<sf::Vector2i> vect, sf::Vector2i max, sf::Vector2i min);
void draw_polygon(sf::RenderWindow &window, sf::Image &screen, std::vector<sf::Vector2i> vect);
unsigned int distance(sf::Vector2i start, sf::Vector2i end);
void xor_fill(sf::RenderWindow &window, sf::Image &screen, std::vector<sf::Vector2i> vect, sf::Vector2i max, sf::Vector2i min);
void xor_line(sf::RenderWindow &window, sf::Image &screen, sf::Vector2i first, sf::Vector2i second);

