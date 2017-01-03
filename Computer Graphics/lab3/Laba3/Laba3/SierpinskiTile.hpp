//
//  SierpinskiTile.hpp
//  Laba3
//
//  Created by Ivan on 12/17/16.
//  Copyright © 2016 Ivan. All rights reserved.
//

#ifndef SierpinskiTile_hpp
#define SierpinskiTile_hpp

#include <stdio.h>
#include <list>
#include <SFML/Graphics.hpp>

class SierpinskiTile
{
public:
    SierpinskiTile(int scrW, int scrH, int w, int h)
    : scrW(scrW), scrH(scrH), tileW(w), tileH(h) {};
    ~SierpinskiTile();
    void setTile(int x_index, int y_index);
    bool isThereTile(int x_index, int y_index);
    void calculate(int y_index = -1);
    void draw(sf::RenderWindow &renderer, int r, int g, int b, int y_index);
    
private:
    int scrW, scrH;
    int tileW, tileH;
    std::list<sf::RectangleShape*> rects;
};

#endif /* SierpinskiTile_hpp */
