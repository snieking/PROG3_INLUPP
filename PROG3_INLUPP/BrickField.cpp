#include "BrickField.hpp"
#include <vector>
#include <algorithm>

namespace game {
    
    BrickField::BrickField(int rows) {
        brickRows = rows;
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