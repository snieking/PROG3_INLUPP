#ifndef Sprite_hpp
#define Sprite_hpp

#include <SDL2/SDL.h>
#include <stdio.h>

class GameEngine;

class Sprite {
public:
    virtual void draw() = 0;
    virtual ~Sprite();
protected:
    Sprite(GameEngine* ge, int x, int y, int w, int h);
    GameEngine* win;
private:
    Sprite(const Sprite&) = delete;
    const Sprite& operator=(const Sprite&) = delete;
    
};

#endif /* Sprite_hpp */
