#include "GameEngine.hpp"
#include "Sprite.hpp"

#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>


namespace game {

    GameEngine::GameEngine(std::string title, int x, int y, int w, int h) {
        // Creating the window where we will draw
        win = SDL_CreateWindow(title.c_str(), x, y, w, h, 0);
        
        // Ceating renderer
        ren = SDL_CreateRenderer(win, -1, 0);
    
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
        SDL_Rect hela { x,y,w,h };
        SDL_RenderFillRect(ren, &hela);
    }
    

    void GameEngine::add(Sprite *sprite) {
        sprites.push_back(sprite);
    }
    
    void GameEngine::run() {
        SDL_RenderClear(ren);
        for (Sprite* s : sprites)
            s->draw();
        SDL_RenderPresent(ren);
    
        bool goOn = true;
        while (goOn) {
            SDL_Event eve;
            while (SDL_PollEvent(&eve)) {
                switch (eve.type) {
                    case SDL_QUIT: goOn = false; break;
                } // switch
            } // inre while
        
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