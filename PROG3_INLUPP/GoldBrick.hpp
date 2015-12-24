#ifndef GoldBrick_hpp
#define GoldBrick_hpp

#include "BrickSprite.hpp"

namespace game {
    class GoldBrick : public BrickSprite {
    public:
        void draw();
        int getDurability() { return durability; }
        void minusDurability() { durability--; }
        void setHit() { hit = true; }
        static GoldBrick* getInstance(GameEngine* ge, int x, int y, int w, int h, int points);
        ~GoldBrick();
    protected:
        GoldBrick(GameEngine* ge, int x, int y, int w, int h, int points);
    private:
        int durability = 3;
        bool hit = false;
        GoldBrick(const GoldBrick&) = delete;
        const GoldBrick& operator=(const GoldBrick&) = delete;
        SDL_Texture* ture;
    };
}

#endif /* GoldBrick_hpp */
