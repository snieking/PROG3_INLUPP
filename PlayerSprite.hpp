//
//  MovingSprite.hpp
//  PROG3_INLUPP
//
//  Created by Viktor Plane on 04/12/15.
//  Copyright © 2015 Viktor Plane. All rights reserved.
//

#ifndef PlayerSprite_hpp
#define PlayerSprite_hpp

#include <SDL2/SDL.h>

#include <stdio.h>
#include "Sprite.hpp"


namespace game {
    
    class PlayerSprite : public Sprite {
    public:
        void draw();
        void moveLeft(const SDL_Event&);
        void mouseRight(const SDL_Event&);
        static PlayerSprite* getInstance(GameEngine* ge, int x, int y, int w, int h);
        ~PlayerSprite();
    protected:
        PlayerSprite(GameEngine* ge, int x, int y, int w, int h);
    private:
        PlayerSprite(const PlayerSprite&) = delete;
        const PlayerSprite& operator=(const PlayerSprite&) = delete;
        SDL_Texture* ture, *paddleIcon;
    };
}

#endif /* PlayerSprite_hpp */
