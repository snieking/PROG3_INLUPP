#include "GameEngine.hpp"
#include "PlayerSprite.hpp"
#include "Sprite.hpp"
#include "Ball.hpp"
#include "LoseScreen.hpp"

#include <stdexcept>
#include <iostream>
#include <SDL2/SDL.h>
#include <random>

#define BRICKWIDTH     100
#define BRICKHEIGHT     50


using namespace std;
using namespace game;

int points = 0;

bool freshGame(GameEngine* ge) {
    
    int level = 5;
    int yVal = 50, xVal = 0;
    
    // Random since c++11
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(0,5);
    int random = 0;
    
    for(int y = 0; y < level; y++) {
        for(int x = 0; x < 8; x++) {
            random = uni(rng);
            switch(random) {
                case 0: {
                    Sprite* blue = Brick::getInstance(ge, xVal, yVal, BRICKWIDTH, BRICKHEIGHT, random);
                    ge->getBrickField()->add(dynamic_cast<Brick*>(blue));
                    break;
                }
                case 1: {
                    Sprite* green = Brick::getInstance(ge, xVal, yVal, BRICKWIDTH, BRICKHEIGHT, random);
                    ge->getBrickField()->add(dynamic_cast<Brick*>(green));
                    break;
                }
                case 2: {
                    Sprite* red = Brick::getInstance(ge, xVal, yVal, BRICKWIDTH, BRICKHEIGHT, random);
                    ge->getBrickField()->add(dynamic_cast<Brick*>(red));
                    break;
                }

                case 3: {
                    Sprite* blue = Brick::getInstance(ge, xVal, yVal, BRICKWIDTH, BRICKHEIGHT, random);
                    ge->getBrickField()->add(dynamic_cast<Brick*>(blue));
                    break;
                }
                case 4: {
                    Sprite* green = Brick::getInstance(ge, xVal, yVal, BRICKWIDTH, BRICKHEIGHT, random);
                    ge->getBrickField()->add(dynamic_cast<Brick*>(green));
                    break;
                }
                case 5: {
                    Sprite* red = Brick::getInstance(ge, xVal, yVal, BRICKWIDTH, BRICKHEIGHT, random);
                    ge->getBrickField()->add(dynamic_cast<Brick*>(red));
                    break;
                }
                    
            }
            xVal += 100;
        }
        xVal = 0;
        yVal += 50;
    }
    
    if(ge->run()) {
        points = ge->totalPoints;
        delete ge;
        return true;
    }
    else {
        points = ge->totalPoints;
        delete ge;
        return false;
    }

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
        
        
        bool gameOn = true;
        if(!(freshGame(ge)))
            gameOn = false;
        while(gameOn){
            //int points = ge->totalPoints;
            cout << "Ska ta bort ge" << endl;
            //delete ge;
            //delete s1;
            //delete s2;
            //delete brickField;
            cout << "Nytt varv freshGame()" << std::endl;
            GameEngine* ge = new GameEngine("Atari Breakout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600);
            Sprite* s1 = PlayerSprite::getInstance(ge, 350, 589, 125, 10);
            ge->setPaddle(dynamic_cast<PlayerSprite*>(s1));
            Sprite* s2 = Ball::getInstance(ge, 400, s1->getY()-20, 20, 20);
            ge->setBall(dynamic_cast<Ball*>(s2));
            BrickField* brickField = new BrickField(9);
            ge->setBrickField(brickField);
            ge->totalPoints = points;
            if(!(freshGame(ge)))
                gameOn = false;
        }
        
        cout << "Färdigt" << endl;
        LoseScreen* ls = new LoseScreen("Atari Breakout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, points);
        ls->show();
        delete ls;
        
    } catch (runtime_error& e) {
        cerr << e.what() << endl;
    }
    return 0;
}
