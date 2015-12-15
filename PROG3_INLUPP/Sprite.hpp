#ifndef Sprite_hpp
#define Sprite_hpp

#include <SDL2/SDL.h>

namespace game {

    class GameEngine;

    class Sprite {
    public:
        virtual void draw() = 0;
        virtual void move(int xPos, int yPos) = 0;
        int getX();
        void setX(int newX);
        int getY();
        virtual ~Sprite();
    protected:
        Sprite(GameEngine* ge, int x, int y, int w, int h);
        GameEngine* win;
        SDL_Rect rect;
    private:
        Sprite(const Sprite&) = delete;
        const Sprite& operator=(const Sprite&) = delete;
    };
    
}

#endif /* Sprite_hpp */
