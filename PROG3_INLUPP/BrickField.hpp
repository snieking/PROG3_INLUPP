#ifndef BrickField_hpp
#define BrickField_hpp

#include "Sprite.hpp"
#include "BrickSprite.hpp"

#include <vector>

namespace game {
    class BrickField {
    public:
        std::vector<BrickSprite*>& getBricks() { return bricks; }
        void add(BrickSprite* brick);
        void remove(BrickSprite* brick);
        void clearAll();
        BrickField(int rows);
        int getBrickRows() const { return brickRows; }
        ~BrickField();
    private:
        int brickRows;
        BrickField(const BrickField&) = delete;
        const BrickField& operator=(const BrickField&) = delete;
        std::vector<BrickSprite*> bricks;
    };
}

#endif /* BrickField_hpp */
