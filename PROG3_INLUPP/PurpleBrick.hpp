#ifndef PurpleBrick_hpp
#define PurpleBrick_hpp

#include "BrickSprite.hpp"

namespace game {
    class PurpleBrick : public BrickSprite {
    public:
        void draw();
        int getDurability() { return durability; }
        void minusDurability() { durability--; }
        void setHit() { hit = true; }
        static PurpleBrick* getInstance(GameEngine* ge, int x, int y, int w, int h, int points);
        ~PurpleBrick();
    protected:
        PurpleBrick(GameEngine* ge, int x, int y, int w, int h, int points);
    private:
        int durability = 2;
        bool hit = false;
        PurpleBrick(const PurpleBrick&) = delete;
        const PurpleBrick& operator=(const PurpleBrick&) = delete;
        SDL_Texture* ture;
    };
}
#endif /* PurpleBrick_hpp */
