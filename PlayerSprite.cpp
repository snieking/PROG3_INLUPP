#include "GameEngine.hpp"
#include "Sprite.hpp"
#include "PlayerSprite.hpp"

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <string>
#include <iostream>


namespace game {
    
    
    PlayerSprite* PlayerSprite::getInstance(GameEngine* ge, int x, int y, int w, int h) {
        return new PlayerSprite(ge, x, y, w, h);
    }
    
    PlayerSprite::PlayerSprite(GameEngine* ge, int x, int y, int w, int h) : Sprite(ge, x, y, w, h) {
        pWidth = w;
        pHeight = h;
        
        SDL_Surface* surf = IMG_Load("/Users/viktorplane/Dropbox/game/greenpaddle.png");
        if(surf == NULL)
            std::cout << "Unable to load image" << std::endl;
      
        ture = SDL_CreateTextureFromSurface(win->getRen(), surf);
        SDL_FreeSurface(surf);
        
    }
    
    void PlayerSprite::move(int xPos, int yPos) {
        rect.x += xPos;
    }

    void PlayerSprite::draw() {
        //std::cout << "Ritade paddel" << std::endl;
        SDL_RenderCopy(win->getRen(), ture, NULL, &rect);
    }
    
    int PlayerSprite::getWidth() {
        return pWidth;
    }
    
    int PlayerSprite::getHeight() {
        return pHeight;
    }
    
    PlayerSprite::~PlayerSprite() {
        SDL_DestroyTexture(ture);
    }
    
}