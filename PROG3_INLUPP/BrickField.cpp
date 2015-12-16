#include "BrickField.hpp"
#include <vector>
#include <algorithm>

namespace game {
    
    BrickField::BrickField(int rows) {
        brickRows = rows;
    }
    
    void BrickField::add(Brick* brick) {
        bricks.push_back(brick);
    }
    
    /*
    void BrickField::remove(Brick* brick) {
        list<Brick*>::iterator pos = find(bricks.begin(), bricks.end(), brick);
    }*/
    
    BrickField::~BrickField() {
        
    }
    
}