
#ifndef GRAPHICS4_LINE_H
#define GRAPHICS4_LINE_H

#include <stdio.h>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>

class Line {
public:
    int  x, y, length;
    double angle;

    Line(){};

    Line(int x, int y, int length, double angle): x(x), y(y), length(length), angle(angle) {};

    Line operator=(const Line& line) {
      if (this != &line) {
        this->x = line.x;
        this->y = line.y;
        this->length = line.length;
        this->angle = line.angle;
      }
      return *this;
    };

    int getX2()  {
      return (int)(x + cos(angle * (M_PI/180)) * length);
    };

    int getY2() {
      return (int)(y + sin(angle * (M_PI/180)) * length);
    };

    void drawLine(sf::RenderWindow &window) {
      sf::Vertex vertex[2] = {
              sf::Vertex(sf::Vector2f(x, y)),
              sf::Vertex(sf::Vector2f(getX2(), getY2()))
      };
      vertex[0].color = sf::Color::Yellow;
      vertex[1].color = sf::Color::Yellow;
      window.draw(vertex, 2, sf::Lines);
      window.display();
    };

};


#endif //GRAPHICS4_LINE_H
