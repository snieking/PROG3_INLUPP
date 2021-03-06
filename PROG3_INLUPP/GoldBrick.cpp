#include "GameEngine.hpp"
#include "GoldBrick.hpp"

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>

namespace game {
    
    GoldBrick* GoldBrick::getInstance(GameEngine* ge, int x, int y, int w, int h, int points) {
        return new GoldBrick(ge, x, y, w, h, points);
    }
    
    GoldBrick::GoldBrick(GameEngine* ge, int x, int y, int w, int h, int points) : BrickSprite(ge, x, y, w, h, points) {
        
        SDL_Surface* surf = IMG_Load("/resources/gold.jpg");
        
        if(surf == NULL)
            std::cout << "Unable to load Brick image" << std::endl;
        
        ture = SDL_CreateTextureFromSurface(win->getRen(), surf);
        SDL_FreeSurface(surf);
        
    }
    
    void GoldBrick::draw() {
        if(durability == 2 && hit == true) {
            SDL_DestroyTexture(ture);
            SDL_Surface* surf = IMG_Load("/resources/gold1.jpg");
            if(surf == NULL)
                std::cout << "Unable to load Gold cracked image" << std::endl;
            ture = SDL_CreateTextureFromSurface(win->getRen(), surf);
            SDL_FreeSurface(surf);
            hit = false;
        }
        else if(durability == 1 && hit == true) {
            SDL_DestroyTexture(ture);
            SDL_Surface* surf = IMG_Load("/resources/gold2MB2.jpg");
            if(surf == NULL)
                std::cout << "Unable to load Gold cracked image" << std::endl;
            ture = SDL_CreateTextureFromSurface(win->getRen(), surf);
            SDL_FreeSurface(surf);
            hit = false;
        }

        SDL_RenderCopy(win->getRen(), ture, NULL, &rect);
    }
    
    GoldBrick::~GoldBrick() {
        if(ture != nullptr)
            SDL_DestroyTexture(ture);
    }
    
    
}