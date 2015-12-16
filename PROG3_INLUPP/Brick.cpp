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
    
    /* Ska inte finnas för Brick, fixa med klasshierarki */
    void Brick::move(int xPos, int yPos) {
        
    }
    
    bool Brick::intersectsWith(Ball* ball) {
        if(rect.x + rect.w < ball->getX() || rect.x > ball->getX() + ball->getWidth() || rect.y + rect.h < ball->getY() || rect.y > ball->getY() + ball->getHeight()) {
            return false;
        } else
            return true;
    }
    
    Brick::Brick(GameEngine* ge, int x, int y, int w, int h, int ident) : Sprite(ge, x, y, w, h) {
        bWidth = w;
        bHeight = h;
        id = ident;
        
        SDL_Surface* surf = nullptr;
        
        switch(ident) {
            case 0: {
                surf = IMG_Load("/Users/viktorplane/Dropbox/game/new/bluebrick.png");
                points = 10;
                break;
            }
            case 1: {
                surf = IMG_Load("/Users/viktorplane/Dropbox/game/new/brownbrick.png");
                points = 5;
                break;
            }
            case 2: {
                surf = IMG_Load("/Users/viktorplane/Dropbox/game/new/purplebrick.png");
                points = 15;
                break;
            }
            case 3: {
                surf = IMG_Load("/Users/viktorplane/Dropbox/game/new/bluebrick.png");
                points = 5;
                break;
            }
            case 4: {
                surf = IMG_Load("/Users/viktorplane/Dropbox/game/new/brownbrick.png");
                points = 10;
                break;
            }
            case 5: {
                surf = IMG_Load("/Users/viktorplane/Dropbox/game/new/bluebrick.png");
                points = 15;
                break;
            }
        }
        
        if(surf == NULL)
            std::cout << "Unable to load Brick image" << std::endl;
        
        ture = SDL_CreateTextureFromSurface(win->getRen(), surf);
        SDL_FreeSurface(surf);
        
    }
    
    void Brick::draw() {
        if(!hit) {
            SDL_RenderCopy(win->getRen(), ture, NULL, &rect);
        }
    }
    
    int Brick::getWidth() {
        return bWidth;
    }
    
    int Brick::getHeight() {
        return bHeight;
    }
    
    Brick::~Brick() {
        SDL_DestroyTexture(ture);
    }
    
    
}