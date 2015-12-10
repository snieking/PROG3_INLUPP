#ifndef Brick_hpp
#define Brick_hpp

#include "Sprite.hpp"
#include <SDL2/SDL.h>

// Ta bort ident

namespace game {
    class Brick : public Sprite {
    public:
        void draw();
        void move(int xPos, int yPos);
        static Brick* getInstance(GameEngine* ge, int x, int y, int w, int h, int ident);
        int getId();
        void setId(int ident);
        bool hit = false;
        ~Brick();
    protected:
        Brick(GameEngine* ge, int x, int y, int w, int h, int ident);
    private:
        int id;
        Brick(const Brick&) = delete;
        const Brick& operator=(const Brick&) = delete;
        SDL_Texture* ture;
    };
}

#endif /* Brick_hpp */
