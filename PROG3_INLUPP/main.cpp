#include "GameEngine.hpp"
#include "PlayerSprite.hpp"
#include "Sprite.hpp"
#include "Ball.hpp"
#include "BrickSprite.hpp"
#include "BlueBrick.hpp"
#include "BrownBrick.hpp"
#include "PurpleBrick.hpp"
#include "GoldBrick.hpp"


#include <stdexcept>
#include <iostream>
#include <SDL2/SDL.h>
#include <random>

#define BRICKWIDTH     100
#define BRICKHEIGHT     50


using namespace std;
using namespace game;

int points = 0;
GameEngine* ge;

int level = 4;
bool freshGame(GameEngine* ge) {
    
    if(level != 7)
        level++;
    int yVal = 50, xVal = 0;
    
    /* Random since c++11 */
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(0,6);
    int random = 0;
    
    for(int y = 0; y < level; y++) {
        for(int x = 0; x < 8; x++) {
            random = uni(rng);
            switch(random) {
                case 0: {
                    Sprite* blue = BlueBrick::getInstance(ge, xVal, yVal, BRICKWIDTH, BRICKHEIGHT, 10);
                    ge->getBrickField()->add(dynamic_cast<BrickSprite*>(blue));
                    break;
                }
                case 1: {
                    Sprite* blue = BlueBrick::getInstance(ge, xVal, yVal, BRICKWIDTH, BRICKHEIGHT, 10);
                    ge->getBrickField()->add(dynamic_cast<BrickSprite*>(blue));
                    break;
                }
                case 2: {
                    Sprite* blue = BlueBrick::getInstance(ge, xVal, yVal, BRICKWIDTH, BRICKHEIGHT, 10);
                    ge->getBrickField()->add(dynamic_cast<BrickSprite*>(blue));
                    break;
                }

                case 3: {
                    Sprite* brown = BrownBrick::getInstance(ge, xVal, yVal, BRICKWIDTH, BRICKHEIGHT, 25);
                    ge->getBrickField()->add(dynamic_cast<BrickSprite*>(brown));
                    break;
                }
                case 4: {
                    Sprite* brown = BrownBrick::getInstance(ge, xVal, yVal, BRICKWIDTH, BRICKHEIGHT, 25);
                    ge->getBrickField()->add(dynamic_cast<BrickSprite*>(brown));
                    break;
                }
                case 5: {
                    Sprite* purple = PurpleBrick::getInstance(ge, xVal, yVal, BRICKWIDTH, BRICKHEIGHT, 60);
                    ge->getBrickField()->add(dynamic_cast<BrickSprite*>(purple));
                    break;
                }
                case 6: {
                    Sprite* gold = GoldBrick::getInstance(ge, xVal, yVal, BRICKWIDTH, BRICKHEIGHT, 100);
                    ge->getBrickField()->add(dynamic_cast<BrickSprite*>(gold));
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
        return true;
    }
    else {
        points = 0;
        level = 4;
        return false;
    }

}

void quit() {
    if(ge != NULL)
        delete ge;
    exit(0);
}

void newGame() {
    try {
        ge = new GameEngine("Atari Breakout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600);
        mfunk hs = &GameEngine::highScore;
        
        
        // Function pointers
        ge->addNShortcut('q', &quit);
        ge->addNShortcut('n', &newGame);
        //ge->addNewGameShortcut('a', newGame);
        
        // Member function pointers
        ge->addShortcut('h', hs);
        mfunk minus = &GameEngine::minusDifficulty;
        ge->addShortcut('1', minus);
        
        mfunk plus = &GameEngine::plusDifficulty;
        ge->addShortcut('2', plus);
        
        ge->setBackgroundPath("/Users/viktorplane/Documents/Pictures/deepspace.png");
        
        //ge->addFunction('1', mfunk);
        
        bool gameOn = true;
        if(!(ge->mainMenu()))
            gameOn = false;
        
        while(gameOn){
            ge->getSprites().clear();
            Sprite* s1 = PlayerSprite::getInstance(ge, 350, 589, 140, 10);
            ge->setPaddle(dynamic_cast<PlayerSprite*>(s1));
            Sprite* s2 = Ball::getInstance(ge, 400, s1->getY()-20, 20, 20);
            ge->setBall(dynamic_cast<Ball*>(s2));
            BrickField* brickField = new BrickField(9);
            ge->setBrickField(brickField);
            
            ge->totalPoints = points;
            
            if(!(freshGame(ge)))
                if(!ge->gameOver())
                    gameOn = false;
                else {
                    if(!ge->mainMenu())
                        gameOn = false;
                }
            
            for(auto cpos = brickField->getBricks().begin(); cpos != brickField->getBricks().end(); cpos++) {
                auto spos = find(ge->getSprites().begin(), ge->getSprites().end(), *cpos);
                ge->getSprites().erase(spos);
                delete *spos;
                *spos = nullptr;
                
            }
            
            ge->getBrickField()->getBricks().clear();
            
        }
        

        delete ge;
        
    } catch (runtime_error& e) {
        cerr << e.what() << endl;
    }
    
}



int main(int argc, const char * argv[]) {
    newGame();
    return 0;
}
