//
//  BrickField.cpp
//  PROG3_INLUPP
//
//  Created by Viktor Plane on 10/12/15.
//  Copyright © 2015 Viktor Plane. All rights reserved.
//

#include "BrickField.hpp"
#include <vector>
#include <algorithm>

namespace game {
    
    BrickField::BrickField(int rows) {
        brickRows = 8;
        
    }
    
    std::vector<Brick*> BrickField::getBricks() {
        return bricks;
    }
    
    int BrickField::getBrickRows() {
        return brickRows;
    }
    
    void BrickField::add(Brick* brick) {
        bricks.push_back(brick);
    }
    
    BrickField::~BrickField() {
        
    }
    
}