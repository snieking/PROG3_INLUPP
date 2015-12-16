#ifndef Ball_hpp
#define Ball_hpp

#include <SDL2/SDL.h>
#include "Sprite.hpp"

namespace game {
    
    class Ball : public Sprite {
    public:
        void draw();
        void move(int xPos, int yPos);
        static Ball* getInstance(GameEngine* ge, int x, int y, int w, int h);
        bool released = false;
        bool goingUp = false;
        bool goingLeft = false;
        int getHeight() { return bHeight; }
        int getWidth() { return bWidth; }
        //void intersectsWith(Brick* brick);
        ~Ball();
    protected:
        Ball(GameEngine* ge, int x, int y, int w, int h);
    private:
        int bWidth, bHeight;
        Ball(const Ball&) = delete;
        const Ball& operator=(const Ball&) = delete;
        SDL_Texture* ture;
    };
}

#endif /* Ball_hpp */
