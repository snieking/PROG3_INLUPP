#include "GameEngine.hpp"
#include "Sprite.hpp"
#include "PlayerSprite.hpp"

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>


namespace game {
    
    
    PlayerSprite* PlayerSprite::getInstance(GameEngine* ge, int x, int y, int w, int h) {
        return new PlayerSprite(ge, x, y, w, h);
    }
    
    PlayerSprite::PlayerSprite(GameEngine* ge, int x, int y, int w, int h) : MovingSprite(ge, x, y, w, h) {

        
        SDL_Surface* surf = IMG_Load("/paddle1.png");
        if(surf == NULL)
            std::cout << "Unable to load image" << std::endl;
      
        ture = SDL_CreateTextureFromSurface(win->getRen(), surf);
        SDL_FreeSurface(surf);
        
    }
    
    void PlayerSprite::move(int xPos, int yPos) {
        rect.x += xPos;
    }

    void PlayerSprite::draw() {
        SDL_RenderCopy(win->getRen(), ture, NULL, &rect);
    }
    
    PlayerSprite::~PlayerSprite() {
        SDL_DestroyTexture(ture);
    }
    
}