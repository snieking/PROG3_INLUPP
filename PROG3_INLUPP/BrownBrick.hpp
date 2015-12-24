#ifndef BrownBrick_hpp
#define BrownBrick_hpp

#include "BrickSprite.hpp"

namespace game {
    class BrownBrick : public BrickSprite {
    public:
        void draw();
        int getDurability() { return durability; }
        void minusDurability() { durability--; }
        void setHit() { hit = true; }
        static BrownBrick* getInstance(GameEngine* ge, int x, int y, int w, int h, int points);
        ~BrownBrick();
    protected:
        BrownBrick(GameEngine* ge, int x, int y, int w, int h, int points);
    private:
        int durability = 1;
        bool hit = false;
        BrownBrick(const BrownBrick&) = delete;
        const BrownBrick& operator=(const BrownBrick&) = delete;
        SDL_Texture* ture;
    };
}

#endif /* BrownBrick_hpp */
