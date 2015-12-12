#include "GameEngine.hpp"
#include "PlayerSprite.hpp"
#include "Sprite.hpp"
#include "Ball.hpp"

#include <stdexcept>
#include <iostream>
#include <SDL2/SDL.h>
#include <random>

#define BRICKWIDTH     100
#define BRICKHEIGHT     50


using namespace std;
using namespace game;

int roll(int min, int max)
{
    // x is in [0,1[
    double x = rand()/static_cast<double>(RAND_MAX+1);
    
    // [0,1[ * (max - min) + min is in [min,max[
    int that = min + static_cast<int>( x * (max - min) );
    
    return that;
}


int main(int argc, const char * argv[]) {
    try {
        GameEngine* ge = new GameEngine("Atari Breakout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600);
        
        Sprite* s1 = PlayerSprite::getInstance(ge, 350, 589, 125, 10);
        ge->setPaddle(dynamic_cast<PlayerSprite*>(s1));
        Sprite* s2 = Ball::getInstance(ge, 400, s1->getY()-20, 20, 20);
        ge->setBall(dynamic_cast<Ball*>(s2));
        
        BrickField* brickField = new BrickField(9);
        ge->setBrickField(brickField);
        
        int level = 5;
        int yVal = 50, xVal = 0;
        
        // Random since cpp 2011
        random_device rd;
        mt19937 rng(rd());
        uniform_int_distribution<int> uni(0,6);
        int random = 0;
        
        for(int y = 0; y < level; y++) {
            for(int x = 0; x < 8; x++) {
                random = uni(rng);
                cout << random << endl;
                switch(random) {
                    case 0: {
                        Sprite* blue = Brick::getInstance(ge, xVal, yVal, BRICKWIDTH, BRICKHEIGHT, random);
                        brickField->add(dynamic_cast<Brick*>(blue));
                        break;
                    }
                    case 1: {
                        Sprite* green = Brick::getInstance(ge, xVal, yVal, BRICKWIDTH, BRICKHEIGHT, random);
                        brickField->add(dynamic_cast<Brick*>(green));
                        cout << "Gör en grön kloss" << endl;
                        break;
                    }
                    case 2: {
                        Sprite* red = Brick::getInstance(ge, xVal, yVal, BRICKWIDTH, BRICKHEIGHT, random);
                        brickField->add(dynamic_cast<Brick*>(red));
                        cout << "Gör en röd kloss" << endl;
                        break;
                    }
                    case 3: {
                        cout << "Gör ingenting" << endl;
                        break;
                    }
                    case 4: {
                        Sprite* blue = Brick::getInstance(ge, xVal, yVal, BRICKWIDTH, BRICKHEIGHT, random);
                        brickField->add(dynamic_cast<Brick*>(blue));
                        break;
                    }
                    case 5: {
                        Sprite* green = Brick::getInstance(ge, xVal, yVal, BRICKWIDTH, BRICKHEIGHT, random);
                        brickField->add(dynamic_cast<Brick*>(green));
                        cout << "Gör en grön kloss" << endl;
                        break;
                    }
                    case 6: {
                        Sprite* red = Brick::getInstance(ge, xVal, yVal, BRICKWIDTH, BRICKHEIGHT, random);
                        brickField->add(dynamic_cast<Brick*>(red));
                        cout << "Gör en röd kloss" << endl;
                        break;
                    }
                
                }
                xVal += 100;
            }
            xVal = 0;
            yVal += 50;
        }
        
        
        // Bricks
        /*
        Sprite* b1 = Brick::getInstance(ge, 0, 200, BRICKWIDTH, BRICKHEIGHT);
        brickField->add(dynamic_cast<Brick*>(b1));
        Sprite* b2 = Brick::getInstance(ge, 100, 200, BRICKWIDTH, BRICKHEIGHT);
        brickField->add(dynamic_cast<Brick*>(b2));
        Sprite* b3 = Brick::getInstance(ge, 200, 200, BRICKWIDTH, BRICKHEIGHT);
        brickField->add(dynamic_cast<Brick*>(b3));
        Sprite* b4 = Brick::getInstance(ge, 300, 200, BRICKWIDTH, BRICKHEIGHT);
        brickField->add(dynamic_cast<Brick*>(b4));
        Sprite* b5 = Brick::getInstance(ge, 400, 200, BRICKWIDTH, BRICKHEIGHT);
        brickField->add(dynamic_cast<Brick*>(b5));
        Sprite* b6 = Brick::getInstance(ge, 500, 200, BRICKWIDTH, BRICKHEIGHT);
        brickField->add(dynamic_cast<Brick*>(b6));
        //Sprite* b7 = Brick::getInstance(ge, 600, 200, BRICKWIDTH, BRICKHEIGHT;
       // brickField->add(dynamic_cast<Brick*>(b7));
        Sprite* b8 = Brick::getInstance(ge, 700, 200, BRICKWIDTH, BRICKHEIGHT);
        brickField->add(dynamic_cast<Brick*>(b8));
        
        
        // Andra raden
        Sprite* b10 = Brick::getInstance(ge, 0, 50, BRICKWIDTH, BRICKHEIGHT);
        brickField->add(dynamic_cast<Brick*>(b10));
        Sprite* b11 = Brick::getInstance(ge, 100, 50, BRICKWIDTH, BRICKHEIGHT);
        brickField->add(dynamic_cast<Brick*>(b11));
        Sprite* b12 = Brick::getInstance(ge, 300, 50, BRICKWIDTH, BRICKHEIGHT);
        brickField->add(dynamic_cast<Brick*>(b12));
        Sprite* b13 = Brick::getInstance(ge, 400, 50, BRICKWIDTH, BRICKHEIGHT);
        brickField->add(dynamic_cast<Brick*>(b13));
        //Sprite* b14 = Brick::getInstance(ge, 600, 50, BRICKWIDTH, BRICKHEIGHT);
        //brickField->add(dynamic_cast<Brick*>(b14));
        Sprite* b15 = Brick::getInstance(ge, 700, 50, BRICKWIDTH, BRICKHEIGHT);
        brickField->add(dynamic_cast<Brick*>(b15));
        */
        
        ge->run();
        
        delete ge;
        delete s1;
        delete s2;
        
    } catch (runtime_error& e) {
        cerr << e.what() << endl;
    }
    return 0;
}
