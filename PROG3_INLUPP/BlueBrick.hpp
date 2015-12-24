#ifndef Brick_hpp
#define Brick_hpp

#include "BrickSprite.hpp"

namespace game {
    class BlueBrick : public BrickSprite {
    public:
        void draw();
        int getDurability() { return durability; }
        void minusDurability() { durability--; }
        void setHit() { hit = true; }
        static BlueBrick* getInstance(GameEngine* ge, int x, int y, int w, int h, int points);
        ~BlueBrick();
    protected:
        BlueBrick(GameEngine* ge, int x, int y, int w, int h, int points);
    private:
        int durability = 1;
        bool hit = false;
        BlueBrick(const BlueBrick&) = delete;
        const BlueBrick& operator=(const BlueBrick&) = delete;
        SDL_Texture* ture;
    };
}

#endif /* Brick_hpp */
