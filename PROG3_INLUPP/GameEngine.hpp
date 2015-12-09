//
//  GameEngine.hpp
//  PROG3_INLUPP
//
//  Created by Viktor Plane on 04/12/15.
//  Copyright © 2015 Viktor Plane. All rights reserved.
//

#ifndef GameEngine_hpp
#define GameEngine_hpp

#include <string>
#include <SDL2/SDL.h>
#include <vector>
#include "Sprite.hpp"
#include "PlayerSprite.hpp"

#define FPS_DELAY 500

namespace game {

class Sprite;

class GameEngine {
public:
    GameEngine(std::string title, int x, int y, int w, int h);
    void add(Sprite* sprite);
    SDL_Renderer* getRen() const; // borde vara privat egentligen
    void run();
    void setPaddle(PlayerSprite* paddle);
    ~GameEngine();
private:
    friend class Sprite;
    SDL_Window* win;
    SDL_Renderer* ren;
    std::vector<Sprite*> sprites;
    PlayerSprite* paddle;
    
    //void clean();
    
    //SDL_Texture* ture;
};
    
}

#endif /* GameEngine_hpp */
