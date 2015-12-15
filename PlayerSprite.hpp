#ifndef PlayerSprite_hpp
#define PlayerSprite_hpp

#include <SDL2/SDL.h>
#include "Sprite.hpp"


namespace game {
    
    class PlayerSprite : public Sprite {
    public:
        void draw();
        void move(int xPos, int yPos);
        static PlayerSprite* getInstance(GameEngine* ge, int x, int y, int w, int h);
        int getWidth(), getHeight();
        
        ~PlayerSprite();
    protected:
        PlayerSprite(GameEngine* ge, int x, int y, int w, int h);
    private:
        int pWidth, pHeight;
        PlayerSprite(const PlayerSprite&) = delete;
        const PlayerSprite& operator=(const PlayerSprite&) = delete;
        SDL_Texture* ture;
    };
}

#endif /* PlayerSprite_hpp */
