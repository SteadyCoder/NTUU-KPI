//
// Created by ivan Tkachenko
//
#ifndef ALGO_H
#define ALGO_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System.hpp>
#include <thread>
#include <mutex>
#include <vector>
#include <math.h>

#define MAX_BUFFER_SIZE 500
const int X(5);
const int Y(5);

extern std::vector<sf::Vector2f> buffer;
extern std::vector<sf::Vector2f> coordinates;
extern int counter;
extern std::mutex gate;

int factorial(int n);

float power(float t, int i);

void bezier_curve(sf::Vector2f *vector, int length, float step);


double get_bezier_basis(int current_point, int num_of_points, float parameter);

void zoom(float scale);

void rotate(float angle);

void transport(sf::Vector2f offset);


#endif
