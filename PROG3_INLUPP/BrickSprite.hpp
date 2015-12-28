#ifndef BrickSprite_hpp
#define BrickSprite_hpp

#include "Sprite.hpp"
#include "Ball.hpp"

namespace game {
    
    class BrickSprite : public Sprite {
    public:
        virtual void draw() = 0;
        int getPoints() const { return points; }
        virtual int getDurability() const = 0;
        virtual void minusDurability() = 0;
        virtual void setHit() = 0;
        bool intersectsWith(Ball* ball);
        ~BrickSprite();
    protected:
        BrickSprite(GameEngine* ge, int x, int y, int w, int h, int p);
    private:
        int points;
        BrickSprite(const BrickSprite&) = delete;
        const BrickSprite& operator=(const BrickSprite&) = delete;
    };
}

#endif /* BrickSprite_hpp */
