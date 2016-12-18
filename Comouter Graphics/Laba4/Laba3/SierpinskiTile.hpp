//
//  SierpinskiTile.hpp
//  Laba3
//
//  Created by Ivan on 12/17/16.
//  Copyright © 2016 Ivan. All rights reserved.
//

#ifndef SierpinskiTile_hpp
#define SierpinskiTile_hpp

#include <list>
#include <SFML/Graphics.hpp>
#include <iostream>

class SierpinskiTile
{
public:
    SierpinskiTile(int screen_width, int screen_height, int w, int h)
    : screen_width(screen_width), screen_height(screen_height), tile_width(w), tile_height(h) {};
    ~SierpinskiTile();
    
    void setTile(int x_index, int y_index);
    bool isThereTile(int x_index, int y_index);
    void calculate(int y_index = -1);
    void draw(sf::RenderWindow &renderer, sf::Color color, int y_index);
    
private:
    int screen_width, screen_height;
    int tile_width, tile_height;
    std::list<sf::RectangleShape*> rects;
};

#endif /* SierpinskiTile_hpp */
