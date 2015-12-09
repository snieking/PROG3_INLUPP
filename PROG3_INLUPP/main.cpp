#include "GameEngine.hpp"
#include "PlayerSprite.hpp"
#include "Sprite.hpp"
#include "Ball.hpp"

#include <stdexcept>
#include <iostream>
#include <SDL2/SDL.h>


using namespace std;
using namespace game;

int main(int argc, const char * argv[]) {
    try {
        GameEngine* ge = new GameEngine("Best game eva", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600);
        
        Sprite* s1 = PlayerSprite::getInstance(ge, 350, 569, 100, 30);
        ge->setPaddle(dynamic_cast<PlayerSprite*>(s1));
        Sprite* s2 = Ball::getInstance(ge, 390, 548, 20, 20);
        ge->setBall(dynamic_cast<Ball*>(s2));
        
        ge->run();
        
        delete ge;
        delete s1;
        delete s2;
        
    } catch (runtime_error& e) {
        cerr << e.what() << endl;
    }
    return 0;
}
