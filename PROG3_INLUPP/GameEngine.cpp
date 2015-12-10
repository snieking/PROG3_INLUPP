#include "GameEngine.hpp"
#include "Sprite.hpp"
#include "PlayerSprite.hpp"

#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>


#include <iostream>


namespace game {

    GameEngine::GameEngine(std::string title, int x, int y, int w, int h) {
        // Creating the window where we will draw
        win = SDL_CreateWindow(title.c_str(), x, y, w, h, 0);
        
        // Ceating renderer
        ren = SDL_CreateRenderer(win, -1, 0);
    
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
        /*SDL_Rect hela { x,y,w,h };
        SDL_RenderFillRect(ren, &hela);*/
    }
    

    void GameEngine::add(Sprite *sprite) {
        //std::cout << "La till en sprite" << std::endl;
        sprites.push_back(sprite);
    }
    
    void GameEngine::setPaddle(PlayerSprite *thePaddle) {
        paddle = thePaddle;
    }
    
    void GameEngine::setBall(Ball *theBall) {
        ball = theBall;
    }
    
    void GameEngine::setBrickField(BrickField *theBrickField) {
        brickField = theBrickField;
    }
    
    void GameEngine::run() {
        // Removes mouse
        SDL_SetRelativeMouseMode(SDL_TRUE);
        int x = 0;
        int ballY = 1, ballX = 1;
        SDL_RenderClear(ren);
        for (Sprite* s : sprites)
            s->draw();
        
        ball->goingLeft = true;
        SDL_RenderPresent(ren);
        bool goOn = true;
        while (goOn) {
            SDL_Event eve;
            while (SDL_PollEvent(&eve)) {
                switch (eve.type) {
                    case SDL_QUIT: goOn = false; break;
                    case SDL_MOUSEMOTION:
                        x = eve.motion.xrel;
                        paddle->move(x,0);
                        if(!ball->released)
                            ball->move(x, 548);
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        if(!ball->released) {
                            ball->released = true;
                            ball->goingUp = true;
                        }
                } // switch
            } // inre while
            
            
            
            // Ifall bollen träffar taket så går den inte upp längre
            if(ball->getY() == 0)
                ball->goingUp = false;
            
            // Ifall bollen träffar en bricka, fungerar bara undersidan av brickan, inte vid sidan
            for(Brick* brick: brickField->getBricks()) {
                if(ball->getY() == brick->getY()+50) {
                    if(brick->getX()-25 <= ball->getX() && ball->getX() <= brick->getX()+99) {
                        // Kollar så att brickan inte redan är träffad TODO: Fungerar inge bra
                        if(!brick->hit) {
                            std::cout << "Träffade en brick" << std::endl;
                            ball->goingUp = false;
                            brickField->remove(brick);
                            brick->hit = true;
                            
                        }
                    }
                }
            }
            
            // Kolla ifall bollen har träffat en vägg
            if(ball->getX() == 0)
                ball->goingLeft = false;
            if(ball->getX() == 800)
                ball->goingLeft = true;
            
            // Bollen ändras till goingUp efter att den 'studsat' på paddeln
            if(ball->getY() == paddle->getY()-20) {
                if(paddle->getX() <= ball->getX() && ball->getX() < paddle->getX()+100) {
                    ball->goingUp = true;
                }
            }
            
            // Görs endast efter bollen har skjutits iväg
            if(ball->released) {
                ball->move(ballX, ballY);
            }
            SDL_RenderClear(ren);
            for (Sprite* s : sprites)
                s->draw();
            
            SDL_RenderPresent(ren);
        } // yttre while
    } // run
     

    SDL_Renderer* GameEngine::getRen() const {
        return ren;
    }

    GameEngine::~GameEngine() {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
    }

}