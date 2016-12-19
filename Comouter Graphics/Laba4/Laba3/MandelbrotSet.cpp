
#include <SFML/Graphics/RenderWindow.hpp>
#include "MandelbrotSet.h"

MandelbrotSet::MandelbrotSet(int screenWidth, int screenHeight, int escapeVal, float graphXMax, float graphXMin,
                             float graphYMax, float graphYMin) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->escapeVal = escapeVal;
    this->graphXMax = graphXMax;
    this->graphXMin = graphXMin;
    this->graphYMax = graphYMax;
    this->graphYMin = graphYMin;
}

void MandelbrotSet::calcMandelbrotFractal(sf::RenderWindow &window, int width, int height) {
    vertexArray.clear();
    float graphX;
    float graphY;
    int escape;
    sf::Vertex vertex;
    for (auto y = 0; y < height; ++y) {
        graphY = pixelToGraph(y, graphYMax - graphYMin, height, graphYMin);
        for (auto x = 0; x < width; ++x) {
            vertex.position = sf::Vector2f(x, y);
            graphX = pixelToGraph(x, graphXMax - graphXMin, height, graphXMin);
            escape = escapeValue(graphX, graphY, escapeVal);
            if (escape == escapeVal)
                vertex.color = sf::Color::Yellow;
            else
                vertex.color = sf::Color::Black;

            vertexArray.append(vertex);
        }
    }
    window.draw(vertexArray);
    window.display();
};

float MandelbrotSet::pixelToGraph(int coord, float graphScale, int imageScale, float graphMin) {
    return ((float)coord * (graphScale / (float)imageScale)) + graphMin;
};


int MandelbrotSet::escapeValue(float realPart, float imaginaryPart, int escapeMax) {
    float zReal = 0, zImag = 0;
    float z0Real = 0, z0Imag = 0;

    for (auto i = 0; i <= escapeMax; ++i) {
        z0Real = (zReal * zReal - zImag * zImag - realPart);
        z0Imag = 2 * zReal * zImag + imaginaryPart;

        if (z0Real * z0Real + z0Imag * z0Imag >= 4)
          return i;

        zReal = z0Real;
        zImag = z0Imag;
    }
    return escapeMax;
};
