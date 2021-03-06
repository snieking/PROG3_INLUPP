#include "LoseScreen.hpp"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <iostream>

namespace game {
    
    LoseScreen::LoseScreen(std::string title, int x, int y, int w, int h, int points) {
        WIDTH = w;
        HEIGHT = h;
        totalPoints = points;
        win = SDL_CreateWindow(title.c_str(), x, y, w, h, 0);
        
        ren = SDL_CreateRenderer(win, -1, 0);
        
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
        
        SDL_Surface* surf = IMG_Load("/Users/viktorplane/Dropbox/game/new/playagain.png");
        if(surf == NULL)
            std::cout << "Unable to load image" << std::endl;
        
        ture = SDL_CreateTextureFromSurface(ren, surf);
        SDL_FreeSurface(surf);
        
        TTF_Init();
        
        f = TTF_OpenFont("/Library/Fonts/Arial Black.ttf", 100);
        textColor = {255, 255, 255};
        
    }
    
    void LoseScreen::show() {
        SDL_SetRelativeMouseMode(SDL_FALSE);
        bool goOn = true;
        while(goOn) {
            SDL_Event eve;
            while (SDL_PollEvent(&eve)) {
                switch (eve.type) {
                    case SDL_QUIT:
                        goOn = false; break;
                } // switch
            } // inner-while
            
            SDL_RenderClear(ren);
            
            
            
            std::string printpoints = "Congratulations, you got " + std::to_string(totalPoints) + " points!";
            
            SDL_Surface* rubrSurf = TTF_RenderText_Solid(f, printpoints.c_str(), textColor);
            
            rubrText = SDL_CreateTextureFromSurface(ren, rubrSurf);
            
            rubrRect = { 50, 250, 700, 100 };
            SDL_Rect picRect = { 300, 350, 150, 150 };
            SDL_FreeSurface(rubrSurf);
            
            SDL_RenderCopy(ren, ture, NULL, &picRect);
            
            
            SDL_RenderCopy(ren, rubrText, NULL, &rubrRect);
            
            SDL_DestroyTexture(rubrText);
            
            SDL_RenderPresent(ren);
            
        } // outer-while
        
    } // show
    
    LoseScreen::~LoseScreen() {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        delete f;
        SDL_DestroyTexture(rubrText);
        SDL_DestroyTexture(ture);
        TTF_Quit();
        SDL_Quit();
        
        
    }
    
    
}
