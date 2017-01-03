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
    rectToAdd->setPosition(x_index * tileW, y_index * tileH);
    rectToAdd->setSize(sf::Vector2f(tileW, tileH));
    
    rects.push_back(rectToAdd);
}

bool SierpinskiTile::isThereTile(int x_index, int y_index) {
    bool result = false;
    
    for (auto itr : rects) {
        sf::Vector2f tmp = itr->getSize();
        if (tmp.x == tileW * x_index && tmp.y == tileH * y_index) {
            result = true;
        }
    }
    return result;
}

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
        
        for (int x = 0; x < scrW / tileW; x++) {
            if ((isThereTile(x, y) || isThereTile(x + 1, y) || isThereTile(x - 1, y))
                && !(isThereTile(x, y) && isThereTile(x + 1, y) && isThereTile(x - 1, y))
                )
                setTile(x, y + 1);
        }
    }
    else {
        for (; y < scrH / tileH; y++)
            for (int x = 0; x < scrW / tileW; x++) {
                if ((isThereTile(x, y) || isThereTile(x + 1, y) || isThereTile(x - 1, y))
                    && !(isThereTile(x, y) && isThereTile(x + 1, y) && isThereTile(x - 1, y))
                    )
                    setTile(x, y + 1);
            }
    }
}

void SierpinskiTile::draw(sf::RenderWindow &renderer, int r, int g, int b, int y_index) {
    sf::Color draw_color = sf::Color::Yellow;
    
    
    std::list<sf::RectangleShape*> deleteRects; //For getting a list of rectangles/tiles to be deleted
    for (auto itr : rects) {
        itr->setFillColor(draw_color);
        
        //Draw all tiles present in the rects which
        //will be just all tiles in the particular row
        renderer.draw(*itr);
        
        if ((itr->getSize()).y <= tileH * y_index)
            //Put all tiles of rows before the given row
            //to deleteRects for deleting
            deleteRects.push_back(itr);
    }
    
    // Delete all collected tiles and clear them
    for (auto itr : deleteRects) {
        rects.remove(itr);
        delete itr;
    }
    deleteRects.clear();
    
}


