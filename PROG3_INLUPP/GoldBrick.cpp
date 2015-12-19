#include "GameEngine.hpp"
#include "GoldBrick.hpp"

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <string>
#include <iostream>

namespace game {
    
    GoldBrick* GoldBrick::getInstance(GameEngine* ge, int x, int y, int w, int h, int points) {
        return new GoldBrick(ge, x, y, w, h, points);
    }
    
    GoldBrick::GoldBrick(GameEngine* ge, int x, int y, int w, int h, int points) : BrickSprite(ge, x, y, w, h, points) {
        
        SDL_Surface* surf = IMG_Load("/Users/viktorplane/Dropbox/game/new/goldbrick.png");
        
        if(surf == NULL)
            std::cout << "Unable to load Brick image" << std::endl;
        
        ture = SDL_CreateTextureFromSurface(win->getRen(), surf);
        SDL_FreeSurface(surf);
        
    }
    
    void GoldBrick::draw() {
        SDL_RenderCopy(win->getRen(), ture, NULL, &rect);
    }
    
    GoldBrick::~GoldBrick() {
        if(ture != nullptr)
            SDL_DestroyTexture(ture);
    }
    
    
}