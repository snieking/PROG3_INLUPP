#include "Ball.hpp"
#include "Sprite.hpp"
#include "GameEngine.hpp"

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <string>
#include <iostream>

namespace game {
    
    Ball* Ball::getInstance(GameEngine* ge, int x, int y, int w, int h) {
        return new Ball(ge, x, y, w, h);
    }
    
    Ball::Ball(GameEngine* ge, int x, int y, int w, int h) : Sprite(ge, x, y, w, h) {
        bWidth = w;
        bHeight = h;
        
        SDL_Surface* surf = IMG_Load("/Users/viktorplane/Documents/git/PROG3_INLUPP/ball.png");
        if(surf == NULL)
            std::cout << "Unable to load ball image" << std::endl;
        
        ture = SDL_CreateTextureFromSurface(win->getRen(), surf);
        SDL_FreeSurface(surf);
        released = false;
        
    }
    
    void Ball::move(int xPos, int yPos) {
        if (!released) {
            rect.x += xPos;
            rect.y = yPos;
        } else {
            if(!goingUp) {
                if(goingLeft) {
                    rect.x -= xPos;
                    rect.y += yPos;
                } else {
                rect.x += xPos;
                rect.y += yPos;
                }
            } else {
                if(goingLeft) {
                rect.x -= xPos;
                rect.y -= yPos;
                } else {
                    rect.x += xPos;
                    rect.y -= yPos;
                }
            }
        }
    }
    
    void Ball::draw() {
        SDL_RenderCopy(win->getRen(), ture, NULL, &rect);
    }
    
    int Ball::getWidth() {
        return bWidth;
    }
    
    int Ball::getHeight() {
        return bHeight;
    }
    
    /*
    void Ball::intersectsWith(Brick* brick) {
        
    }*/
    
    Ball::~Ball() {
        SDL_DestroyTexture(ture);
    }
}
