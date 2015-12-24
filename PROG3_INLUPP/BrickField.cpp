#include "BrickField.hpp"

#include <vector>

namespace game {
    
    BrickField::BrickField(int rows) {
        brickRows = rows;
    }
    
    void BrickField::add(BrickSprite* brick) {
        bricks.push_back(brick);
    }
    
    
    void BrickField::remove(BrickSprite* brick) {
        auto pos = find(bricks.begin(), bricks.end(), brick);
        bricks.erase(pos);
    }
    
    
    void BrickField::clearAll() {
        
    }
    
    BrickField::~BrickField() {
        
    }
    
}