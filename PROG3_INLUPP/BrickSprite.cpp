//
//  BrickSprite.cpp
//  PROG3_INLUPP
//
//  Created by Viktor Plane on 19/12/15.
//  Copyright © 2015 Viktor Plane. All rights reserved.
//

#include "BrickSprite.hpp"

namespace game {
    BrickSprite::BrickSprite(GameEngine* ge, int x,int y, int w, int h, int p) : Sprite(ge, x, y, w, h) {
        points = p;
    }
    
    bool BrickSprite::intersectsWith(Ball* ball) {
        if(rect.x + rect.w < ball->getX() || rect.x > ball->getX() + ball->getWidth() || rect.y + rect.h < ball->getY() || rect.y > ball->getY() + ball->getHeight()) {
            return false;
        } else
            return true;
    }
    
    BrickSprite::~BrickSprite() {}
}
