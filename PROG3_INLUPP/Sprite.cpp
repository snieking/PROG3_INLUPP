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

    Sprite::~Sprite() {
    
    }
    
}
