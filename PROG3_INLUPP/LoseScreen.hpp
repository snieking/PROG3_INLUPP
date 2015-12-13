#ifndef LoseScreen_hpp
#define LoseScreen_hpp

#include "LoseScreen.hpp"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

namespace game {
    class LoseScreen {
    public:
        LoseScreen(std::string title, int x, int y, int w, int h, int points);
        void show();
        ~LoseScreen();
    private:
        int WIDTH, HEIGHT, totalPoints;
        SDL_Window* win;
        SDL_Renderer* ren;
        SDL_Color textColor;
        TTF_Font* f;
        SDL_Rect rubrRect;
        SDL_Texture* rubrText;
        
    };
}

#endif /* LoseScreen_hpp */
