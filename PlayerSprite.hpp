#ifndef PlayerSprite_hpp
#define PlayerSprite_hpp

#include "Sprite.hpp"
#include "MovingSprite.hpp"


namespace game {
    
    class PlayerSprite : public MovingSprite {
    public:
        void draw();
        void move(int xPos, int yPos);
        static PlayerSprite* getInstance(GameEngine* ge, int x, int y, int w, int h);
        ~PlayerSprite();
    protected:
        PlayerSprite(GameEngine* ge, int x, int y, int w, int h);
    private:
        PlayerSprite(const PlayerSprite&) = delete;
        const PlayerSprite& operator=(const PlayerSprite&) = delete;
        SDL_Texture* ture;
    };
}

#endif /* PlayerSprite_hpp */
