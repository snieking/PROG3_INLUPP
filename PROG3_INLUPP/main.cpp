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
        
        
        BrickField* brickField = new BrickField(9);
        ge->setBrickField(brickField);
        
        // Bricks
        int id = 0;
        Sprite* b1 = Brick::getInstance(ge, 0, 0, 100, 50, id++);
        brickField->add(dynamic_cast<Brick*>(b1));
        Sprite* b2 = Brick::getInstance(ge, 100, 0, 100, 50, id++);
        brickField->add(dynamic_cast<Brick*>(b2));
        Sprite* b3 = Brick::getInstance(ge, 200, 0, 100, 50, id++);
        brickField->add(dynamic_cast<Brick*>(b3));
        Sprite* b4 = Brick::getInstance(ge, 300, 0, 100, 50, id++);
        brickField->add(dynamic_cast<Brick*>(b4));
        Sprite* b5 = Brick::getInstance(ge, 400, 0, 100, 50, id++);
        brickField->add(dynamic_cast<Brick*>(b5));
        Sprite* b6 = Brick::getInstance(ge, 500, 0, 100, 50, id++);
        brickField->add(dynamic_cast<Brick*>(b6));
        Sprite* b7 = Brick::getInstance(ge, 600, 0, 100, 50, id++);
        brickField->add(dynamic_cast<Brick*>(b7));
        Sprite* b8 = Brick::getInstance(ge, 700, 0, 100, 50, id++);
        brickField->add(dynamic_cast<Brick*>(b8));
        /*Sprite* b9 = Brick::getInstance(ge, 800, 0, 100, 50, id++);
        brickField->add(dynamic_cast<Brick*>(b9)); */
        
        // Andra raden
        Sprite* b10 = Brick::getInstance(ge, 0, 50, 100, 50, id++);
        brickField->add(dynamic_cast<Brick*>(b10));
        Sprite* b11 = Brick::getInstance(ge, 100, 50, 100, 50, id++);
        brickField->add(dynamic_cast<Brick*>(b11));
        Sprite* b12 = Brick::getInstance(ge, 300, 50, 100, 50, id++);
        brickField->add(dynamic_cast<Brick*>(b12));
        Sprite* b13 = Brick::getInstance(ge, 400, 50, 100, 50, id++);
        brickField->add(dynamic_cast<Brick*>(b13));
        Sprite* b14 = Brick::getInstance(ge, 600, 50, 100, 50, id++);
        brickField->add(dynamic_cast<Brick*>(b14));
        Sprite* b15 = Brick::getInstance(ge, 700, 50, 100, 50, id++);
        brickField->add(dynamic_cast<Brick*>(b15));

        
        ge->run();
        
        delete ge;
        delete s1;
        delete s2;
        
    } catch (runtime_error& e) {
        cerr << e.what() << endl;
    }
    return 0;
}
