#include "GameEngine.hpp"
#include "PurpleBrick.hpp"

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <string>
#include <iostream>

namespace game {
    
    PurpleBrick* PurpleBrick::getInstance(GameEngine* ge, int x, int y, int w, int h, int points) {
        return new PurpleBrick(ge, x, y, w, h, points);
    }
    
    PurpleBrick::PurpleBrick(GameEngine* ge, int x, int y, int w, int h, int points) : BrickSprite(ge, x, y, w, h, points) {
        
        SDL_Surface* surf = IMG_Load("/Users/viktorplane/Dropbox/game/new/purplebrick.png");
        
        if(surf == NULL)
            std::cout << "Unable to load Brick image" << std::endl;
        
        ture = SDL_CreateTextureFromSurface(win->getRen(), surf);
        SDL_FreeSurface(surf);
        
    }
    
    void PurpleBrick::draw() {
        SDL_RenderCopy(win->getRen(), ture, NULL, &rect);
    }
    
    PurpleBrick::~PurpleBrick() {
        if(ture != nullptr)
            SDL_DestroyTexture(ture);
    }
    
    
}