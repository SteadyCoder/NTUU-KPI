//
//  sierpinski_alogrithm.hpp
//  Laba3
//
//  Created by Ivan on 12/17/16.
//  Copyright © 2016 Ivan. All rights reserved.
//

#ifndef sierpinski_alogrithm_hpp
#define sierpinski_alogrithm_hpp

#include "SierpinskiTile.hpp"

// Row of screen
static int row = 0;

// You should pass your tile here
// But before passing you shoudl create it before your while loop like this:
// *****************************************
//  SierpinskiTile *tile = new SierpinskiTile(screen_width, screen_height, tile_width, tile_height);
//  tile->setTile((screen_width / tile_width) / 2, 0);
// *****************************************

void algorithm(int screen_width, int screen_height, int tile_width, int tile_height, sf::RenderWindow &window, SierpinskiTile *tile, sf::Color main_color) {
    sf::Color draw_color = main_color;
    
    if (row < screen_height / tile_height) {
        tile->draw(window, draw_color, row - 1);
        tile->calculate(row++);
    } else {
        row = 0;
    }
}


#endif /* sierpinski_alogrithm_hpp */
