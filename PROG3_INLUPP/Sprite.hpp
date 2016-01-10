#ifndef Sprite_hpp
#define Sprite_hpp

#include <SDL2/SDL.h>

namespace game {

    class GameEngine;

    class Sprite {
    public:
        virtual void draw() = 0;
        int getX() const { return rect.x; }
        void setX(int newX);
        int getY() const { return rect.y; }
        int getWidth() const { return rect.w; }
        int getHeight() const { return rect.h; }
        virtual ~Sprite() {}
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
