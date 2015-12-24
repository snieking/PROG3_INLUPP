#include "GameEngine.hpp"
#include "BlueBrick.hpp"
#include "BrickSprite.hpp"

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>

namespace game {
    
    BlueBrick* BlueBrick::getInstance(GameEngine* ge, int x, int y, int w, int h, int points) {
        return new BlueBrick(ge, x, y, w, h, points);
    }

    BlueBrick::BlueBrick(GameEngine* ge, int x, int y, int w, int h, int points) : BrickSprite(ge, x, y, w, h, points) {
        
        SDL_Surface* surf = IMG_Load("/Users/viktorplane/Dropbox/game/new/bluebrick.png");
        
        if(surf == NULL)
            std::cout << "Unable to load Brick image" << std::endl;
        
        ture = SDL_CreateTextureFromSurface(win->getRen(), surf);
        SDL_FreeSurface(surf);
        
    }
    
    void BlueBrick::draw() {
        SDL_RenderCopy(win->getRen(), ture, NULL, &rect);
    }
    
    BlueBrick::~BlueBrick() {
        if(ture != nullptr)
            SDL_DestroyTexture(ture);
    }
    
    
}