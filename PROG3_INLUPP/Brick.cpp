#include "GameEngine.hpp"
#include "Brick.hpp"
#include "Sprite.hpp"

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <string>
#include <iostream>

namespace game {
    
    Brick* Brick::getInstance(GameEngine* ge, int x, int y, int w, int h, int ident) {
        return new Brick(ge, x, y, w, h, ident);
    }
    
    void Brick::move(int xPos, int yPos) {
        
    }
    
    /*
    void Brick::setId(int ident) {
        id = ident;
    }*/
    
    int Brick::getId() {
        return id;
    }
    
    Brick::Brick(GameEngine* ge, int x, int y, int w, int h, int ident) : Sprite(ge, x, y, w, h) {
        id = ident;
        SDL_Surface* surf = IMG_Load("/Users/viktorplane/Documents/git/PROG3_INLUPP/block.png");
        if(surf == NULL)
            std::cout << "Unable to load Brick image" << std::endl;
        
        ture = SDL_CreateTextureFromSurface(win->getRen(), surf);
        SDL_FreeSurface(surf);
        
    }
    
    void Brick::draw() {
        if(!hit)
            SDL_RenderCopy(win->getRen(), ture, NULL, &rect);
    }
    
    Brick::~Brick() {
        SDL_DestroyTexture(ture);
    }
    
    
}