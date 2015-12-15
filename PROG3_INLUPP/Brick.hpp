#ifndef Brick_hpp
#define Brick_hpp

#include "Sprite.hpp"
#include "Ball.hpp"
#include <SDL2/SDL.h>

/* Fixa så att brickor tas bort ifall träffade */

namespace game {
    class Brick : public Sprite {
    public:
        void draw();
        void move(int xPos, int yPos);
        static Brick* getInstance(GameEngine* ge, int x, int y, int w, int h, int ident);
        bool hit = false;
        int getWidth(), getHeight();
        bool intersectsWith(Ball* ball);
        int points;
        ~Brick();
    protected:
        Brick(GameEngine* ge, int x, int y, int w, int h, int ident);
    private:
        int bWidth, bHeight, id;
        Brick(const Brick&) = delete;
        const Brick& operator=(const Brick&) = delete;
        SDL_Texture* ture;
    };
}

#endif /* Brick_hpp */
