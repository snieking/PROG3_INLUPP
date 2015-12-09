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
        ~Ball();
    protected:
        Ball(GameEngine* ge, int x, int y, int w, int h);
    private:
        Ball(const Ball&) = delete;
        const Ball& operator=(const Ball&) = delete;
        SDL_Texture* ture;
    };
}

#endif /* Ball_hpp */
