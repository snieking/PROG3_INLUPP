//
//  GameEngine.hpp
//  PROG3_INLUPP
//
//  Created by Viktor Plane on 04/12/15.
//  Copyright © 2015 Viktor Plane. All rights reserved.
//

#ifndef GameEngine_hpp
#define GameEngine_hpp

#include <stdio.h>
#include <string>
#include <SDL2/SDL.h>
#include <vector>

class Sprite;

class GameEngine {
public:
    GameEngine(std::string title, int x, int y, int w, int h);
    void add(Sprite* sprite);
    SDL_Renderer* getRen() const; // borde vara privat egentligen
    void run();
    ~GameEngine();
private:
    friend class Sprite;
    SDL_Window* win;
    SDL_Renderer* ren;
    std::vector<Sprite*> sprites;
    
};

#endif /* GameEngine_hpp */
