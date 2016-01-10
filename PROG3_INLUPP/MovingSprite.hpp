#ifndef MovingSprite_hpp
#define MovingSprite_hpp

#include "Sprite.hpp"

namespace game {
    class MovingSprite : public Sprite {
    public:
        virtual void draw() = 0;
        virtual void move(int xPos, int yPos) = 0;
        virtual ~MovingSprite() {}
    protected:
        MovingSprite(GameEngine* ge, int x, int y, int w, int h);
    private:
        MovingSprite(const MovingSprite&) = delete;
        const MovingSprite& operator=(const MovingSprite&) = delete;
        
    };
}

#endif /* MovingSprite_hpp */
