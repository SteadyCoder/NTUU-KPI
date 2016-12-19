#ifndef GRAPHICS4_MANDELBROTSET_H
#define GRAPHICS4_MANDELBROTSET_H

#include <SFML/Window.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>

class MandelbrotSet {
private:
    int screenWidth, screenHeight;
    int escapeVal;
    float graphXMax, graphXMin;
    float graphYMax, graphYMin;
    sf::VertexArray vertexArray;

public:
    MandelbrotSet(){};
    MandelbrotSet(int screenWidth, int screenHeight, int escapeVal, float graphXMax, float graphXMin, float graphYMax, float graphYMin);
    void calcMandelbrotFractal(sf::RenderWindow &window, int width, int height);
    float pixelToGraph(int coord, float graphScale, int imageScale, float graphMin);
    int escapeValue(float realPart, float imaginaryPart, int escapeMax);
};


#endif //GRAPHICS4_MANDELBROTSET_H
