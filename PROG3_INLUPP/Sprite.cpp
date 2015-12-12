//
//  Sprite.cpp
//  PROG3_INLUPP
//
//  Created by Viktor Plane on 04/12/15.
//  Copyright © 2015 Viktor Plane. All rights reserved.
//

#include "Sprite.hpp"
#include "GameEngine.hpp"

namespace game {

    Sprite::Sprite(GameEngine* ge, int x, int y, int w, int h) :win(ge), rect { x,y,w,h } {
        ge->add(this);
    }
    
    
    int Sprite::getX() {
        return rect.x;
    }
    
    void Sprite::setX(int newX) {
        rect.x = newX;
    }
    
    int Sprite::getY() {
        return rect.y;
    }

    Sprite::~Sprite() {
    
    }
    
}
