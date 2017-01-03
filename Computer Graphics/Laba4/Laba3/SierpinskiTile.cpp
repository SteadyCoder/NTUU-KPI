//
//  SierpinskiTile.cpp
//  Laba3
//
//  Created by Ivan on 12/17/16.
//  Copyright © 2016 Ivan. All rights reserved.
//

#include "SierpinskiTile.hpp"

SierpinskiTile::~SierpinskiTile() {
    for (auto itr : rects)
        delete itr;
}

void SierpinskiTile::setTile(int x_index, int y_index) {
    sf::RectangleShape *rectToAdd = new sf::RectangleShape();
    rectToAdd->setPosition(x_index * tile_width, y_index * tile_height);
    rectToAdd->setSize(sf::Vector2f(tile_width, tile_height));
    
    rects.push_back(rectToAdd);
}

bool SierpinskiTile::isThereTile(int x_index, int y_index) {
    bool result = false;
    
    for (auto itr : rects) {
        sf::Vector2f tmp = itr->getPosition();
        if (tmp.x == tile_width * x_index && tmp.y == tile_height * y_index) {
            result = true;
        }
    }
    return result;
}

// Figure out how it works
void SierpinskiTile::calculate(int y_index) {
//Calculating where to put tiles in the next row
//by the tile arrangement present in the previous row

    /////////////////////////////////////////////////
    //Conditions for putting a tile below the upper tile (or tile space):
    // 1- Tile is at that spot, 0- Tile is not at that spot, X- Unknown (can be 0 or 1)
    
    /////////////////////////////////////////////////
    // Case 1: 0 1 0, Case 2: 1 0 0, Case 3: 0 0 1,
    // Case 4: 1 1 0, Case 5: 1 0 1, Case 6: 0 1 1
    
    // Output for Cases 1-6: X 1 X
    
    /////////////////////////////////////////////////
    // Case 7: 0 0 0, Case 8: 1 1 1
    
    // Output for Cases 7-8: X 0 X
    
    int y = 0;
    if (y_index > -1) {
        y = y_index;
        
        for (int x = 0; x < screen_width / tile_width; x++) {
            if ((isThereTile(x, y) || isThereTile(x + 1, y) || isThereTile(x - 1, y))
                && !(isThereTile(x, y) && isThereTile(x + 1, y) && isThereTile(x - 1, y))
                )
                setTile(x, y + 1);
        }
    }
    else {
        for (; y < screen_height / tile_height; y++)
            for (int x = 0; x < screen_width / tile_width; x++) {
                if ((isThereTile(x, y) || isThereTile(x + 1, y) || isThereTile(x - 1, y))
                    && !(isThereTile(x, y) && isThereTile(x + 1, y) && isThereTile(x - 1, y))
                    )
                    setTile(x, y + 1);
            }
    }
}

void SierpinskiTile::draw(sf::RenderWindow &renderer, sf::Color color, int y_index) {
    
    // Draw all tiles present in the rects which
    // will be just all tiles in the particular row
    for (auto itr : rects) {
        itr->setFillColor(color);
        renderer.draw(*itr);
    }
}
