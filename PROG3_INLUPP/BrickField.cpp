#include "BrickField.hpp"
#include <vector>
#include <algorithm>
#include <iostream>

namespace game {
    
    BrickField::BrickField(int rows) {
        brickRows = rows;
    }
    
    void BrickField::add(Brick* brick) {
        bricks.push_back(brick);
    }
    
    
    void BrickField::remove(Brick* brick) {
        auto pos = find(bricks.begin(), bricks.end(), brick);
        std::cout << "Innan: " << bricks.size() << std::endl;
        bricks.erase(pos);
        std::cout << "Efter: " << bricks.size() << std::endl;
    }
    
    BrickField::~BrickField() {
        
    }
    
}