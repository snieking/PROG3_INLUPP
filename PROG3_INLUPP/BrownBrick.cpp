#include "GameEngine.hpp"
#include "BrownBrick.hpp"

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>

namespace game {
    
    BrownBrick* BrownBrick::getInstance(GameEngine* ge, int x, int y, int w, int h, int points) {
        return new BrownBrick(ge, x, y, w, h, points);
    }
    
    BrownBrick::BrownBrick(GameEngine* ge, int x, int y, int w, int h, int points) : BrickSprite(ge, x, y, w, h, points) {
        
        SDL_Surface* surf = IMG_Load("/Users/viktorplane/Dropbox/game/new/brownbrick.png");
        
        if(surf == NULL)
            std::cout << "Unable to load Brick image" << std::endl;
        
        ture = SDL_CreateTextureFromSurface(win->getRen(), surf);
        SDL_FreeSurface(surf);
        
    }
    
    void BrownBrick::draw() {
        SDL_RenderCopy(win->getRen(), ture, NULL, &rect);
    }
    
    BrownBrick::~BrownBrick() {
        if(ture != nullptr)
            SDL_DestroyTexture(ture);
    }
    
    
}