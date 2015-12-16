#ifndef BrickField_hpp
#define BrickField_hpp

#include "Sprite.hpp"
#include "Brick.hpp"
#include <vector>

namespace game {
    class BrickField {
    public:
        std::vector<Brick*> getBricks() { return bricks; }
        void add(Brick* brick);
        BrickField(int rows);
        int getBrickRows() { return brickRows; }
        ~BrickField();
    private:
        int brickRows;
        BrickField(const BrickField&) = delete;
        const BrickField& operator=(const BrickField&) = delete;
        std::vector<Brick*> bricks;
    };
}

#endif /* BrickField_hpp */
