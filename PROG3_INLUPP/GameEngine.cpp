#include "GameEngine.hpp"
#include "Sprite.hpp"
#include "PlayerSprite.hpp"

#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_ttf/SDL_ttf.h>

#include <iostream>

namespace game {

    GameEngine::GameEngine(std::string title, int x, int y, int w, int h) {
        WIDTH = w;
        HEIGHT = h;
        
        win = SDL_CreateWindow(title.c_str(), x, y, w, h, 0);
        ren = SDL_CreateRenderer(win, -1, 0);
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
 
        TTF_Init();
        
        f = TTF_OpenFont("/resources/Arial Black.ttf", 100);
        textColor = {255, 255, 255};
    }
    
    void GameEngine::plusDifficulty() {
        if(timePerFrame != 0)
            timePerFrame--;
    }
    
    void GameEngine::add(Sprite *sprite) {
        sprites.push_back(sprite);
    }
    
    void GameEngine::remove(Sprite *sprite) {
        auto pos = find(sprites.begin(), sprites.end(), sprite);
        sprites.erase(pos);
    }
    
    void GameEngine::addShortcut(char c, mfunk f) {
        functions.insert({c, f});
    }
    
    void GameEngine::addNShortcut(char c, std::function<void()> nf) {
        nfuncs.insert({c, nf});
    }
    
    void GameEngine::setPaddle(PlayerSprite *thePaddle) {
        paddle = thePaddle;
    }
    
    void GameEngine::setBall(Ball *theBall) {
        ball = theBall;
    }
    
    void GameEngine::setBrickField(BrickField *theBrickField) {
        brickField = theBrickField;
    }
    
    BrickField* GameEngine::getBrickField() {
        return brickField;
    }
    
    bool GameEngine::mainMenu() {
        SDL_SetRelativeMouseMode(SDL_FALSE);
        
        int newGameX = (WIDTH/2)-100, newGameY = (HEIGHT/2)-75, newGameW = 250, newGameH = 75;
        int highscoreX = (WIDTH/2)-100, highscoreY = newGameY+newGameH+10, highscoreW = newGameW, highscoreH = newGameH;
        int plusMinusX = 455, plusMinusY = 400, plusMinusW = 20, plusMinusH = 60;
        
        // new game button
        SDL_Surface* newGameSurf = IMG_Load("/resources/playGame.png");
        if(newGameSurf == NULL)
            std::cout << "Unable to load image" << std::endl;
        newGameTexture = SDL_CreateTextureFromSurface(ren, newGameSurf);
        SDL_FreeSurface(newGameSurf);
        SDL_Rect newGameRect = { newGameX, newGameY, newGameW, newGameH };
        willStartGame = false;
        
        // highscore button
        SDL_Surface* highscoreSurf = IMG_Load("/resources/scores.png");
        if(highscoreSurf == NULL)
            std::cout << "Unable to load image" << std::endl;
        
        highscoreTexture = SDL_CreateTextureFromSurface(ren, highscoreSurf);
        SDL_FreeSurface(highscoreSurf);
        SDL_Rect highscoreRect = { highscoreX, highscoreY, highscoreW, highscoreH };
        
        // plusMinus Button
        SDL_Surface* plusMinusSurf = IMG_Load("/resources/plusminus.png");
        if(plusMinusSurf == NULL)
            std::cout << "Unable to load plusMinus image" << std::endl;
        
        plusMinusText = SDL_CreateTextureFromSurface(ren, plusMinusSurf);
        SDL_FreeSurface(plusMinusSurf);
        SDL_Rect plusMinusRect = { plusMinusX, plusMinusY, plusMinusW, plusMinusH };
        
        // difficulty rect
        SDL_Rect difficultyRect = { 345, 400, 100, 60 };
        
        // created by text
        std::string createdBy = "Viktor Plane and Olof Hofstedt (PROG3 2015-16)";
        SDL_Surface* createdBySurf = TTF_RenderText_Solid(f, createdBy.c_str(), textColor);
        createdByText = SDL_CreateTextureFromSurface(ren, createdBySurf);
        SDL_FreeSurface(createdBySurf);
        createdByRect = { WIDTH - (WIDTH/2)-10, HEIGHT-25, WIDTH/2, 20 };
        
        // background text
        if(backgroundPath.length() != 0) {
            SDL_Surface* backgroundSurf = IMG_Load(backgroundPath.c_str());
            backgroundTexture = SDL_CreateTextureFromSurface(ren, backgroundSurf);
            SDL_FreeSurface(backgroundSurf);
        }
        
        bool goOn = true;
        while(goOn) {
            SDL_Event eve;
            while(SDL_PollEvent(&eve)) {
                switch (eve.type) {
                    case SDL_QUIT:
                        goOn = false; break;
                    case SDL_MOUSEBUTTONDOWN:
                        if (eve.button.x >= newGameX && eve.button.x <= newGameX+newGameW && eve.button.y >= newGameY && eve.button.y <= newGameY+newGameH) {
                            willStartGame = true;
                            goOn = false;
                            break;
                        }
                        if (eve.button.x >= highscoreX && eve.button.x <= highscoreX+highscoreW && eve.button.y >= highscoreY && eve.button.y <= highscoreY+highscoreH) {
                            highScore();
                            break;
                        }
                        if (eve.button.x >= plusMinusX && eve.button.x <= plusMinusX+plusMinusW) {
                            if(eve.button.y >= plusMinusY && eve.button.y <= plusMinusY+(plusMinusH/2))
                                minusDifficulty();
                            else if(eve.button.y >= plusMinusY+(plusMinusH/2) && eve.button.y <= plusMinusY+plusMinusH)
                                plusDifficulty();
                        }
                    case SDL_KEYDOWN:
                        char a = eve.key.keysym.sym;
                        
                        if(functions.count(a)>0) {
                            mfunk m = functions[a];
                            (this->*m)();
                        }
                        else if(nfuncs.count(a)>0) {
                            std::function<void()> nfunk = nfuncs[a];
                            nfunk();
                        }
   
                } // switch
            } // inner while
            
            SDL_RenderClear(ren);
            
            // background image
            if(backgroundTexture != nullptr)
                SDL_RenderCopy(ren, backgroundTexture, NULL, NULL);
            
            // difficulty text
            std::string difficulty = "Handicap: " + getDifficulty();
            SDL_Surface* difficultySurf = TTF_RenderText_Solid(f, difficulty.c_str(), textColor);
            difficultyText = SDL_CreateTextureFromSurface(ren, difficultySurf);
            SDL_FreeSurface(difficultySurf);
            
            SDL_RenderCopy(ren, newGameTexture, NULL, &newGameRect);
            SDL_RenderCopy(ren, highscoreTexture, NULL, &highscoreRect);
            SDL_RenderCopy(ren, plusMinusText, NULL, &plusMinusRect);
            SDL_RenderCopy(ren, difficultyText, NULL, &difficultyRect);
            SDL_RenderCopy(ren, createdByText, NULL, &createdByRect);

            SDL_RenderPresent(ren);
            
            // destroy texture
            SDL_DestroyTexture(difficultyText);
        } // outer while
        SDL_DestroyTexture(newGameTexture);
        SDL_DestroyTexture(highscoreTexture);
        SDL_DestroyTexture(plusMinusText);
        SDL_DestroyTexture(createdByText);
        
        return willStartGame;
    } // main menu
    
  
    
    bool GameEngine::newGame() {

        // removes mouse
        SDL_SetRelativeMouseMode(SDL_TRUE);
        
        newGameInitialized = true;
        gameWon = false;

        int x = 0;
        int ballY = 1, ballX = 0;
        int varv = 0;

        for (Sprite* s : sprites)
            s->draw();
        
        ball->goingLeft = true;
        SDL_RenderPresent(ren);
        Uint32 startTime = SDL_GetTicks();
        
        bool goOn = true;
        while (goOn) {
            Uint32 elapsedMS = SDL_GetTicks() - startTime;
            Uint32 start = SDL_GetTicks() + timePerFrame;
            SDL_Event eve;
            while (SDL_PollEvent(&eve)) {
                switch (eve.type) {
                    case SDL_QUIT: goOn = false; break;
                    case SDL_MOUSEMOTION:
                        x = eve.motion.xrel;
                        paddle->move(x,0);
                        if(!ball->released)
                            ball->move(x, paddle->getY()-ball->getHeight());
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        if(!ball->released) {
                            ball->released = true;
                            ball->goingUp = true;
                        }
                    case SDL_KEYDOWN:
                        char a = eve.key.keysym.sym;
                        
                        if(nfuncs.count(a)>0) {
                            std::function<void()> nfunk = nfuncs[a];
                            nfunk();
                        }
                } // switch
            } // inner while
            
            // fps counter
            if (varv % 10 == 0) {
                double elapsedSeconds = elapsedMS / 1000.0;
                double averageFps = varv / elapsedSeconds;
                int averageIntFps = averageFps;
                std::string varvStr = "FPS: " + std::to_string(averageIntFps);
                SDL_Surface* varvSurf = TTF_RenderText_Solid(f, varvStr.c_str(), textColor);
                if (varvText != nullptr && varv != 0)
                    SDL_DestroyTexture(varvText);
                varvText = SDL_CreateTextureFromSurface(ren, varvSurf);
                varvRect.w = 75;
                varvRect.h = 25;
                varvRect.x = WIDTH-varvRect.w-10;
                varvRect.y = 10;
                SDL_FreeSurface(varvSurf);
                
            }
            
            varv++;
            
            // ifall bollen träffar taket så går den ner istället
            if(ball->getY() == 0)
                ball->goingUp = false;
            
            brickRemoved = false;
            
            for(BrickSprite* brick: brickField->getBricks()) {
                if(!brickRemoved)
                    if(brick->intersectsWith(ball)) {
                        brick->minusDurability();
                        brick->setHit();
                        if(brick->getDurability() < 1) {
                            totalPoints += brick->getPoints();
                            brickField->remove(brick);
                            remove(brick);
                        }
                        brickRemoved = true;
                    }
            }
            
            // kolla ifall bollen har träffat en vägg
            if(ball->getX() <= 0)
                ball->goingLeft = false;
            if(ball->getX()+ball->getWidth() >= 800)
                ball->goingLeft = true;
            
            // bollen ändras till goingUp efter att den 'studsat' på paddeln
            if(ball->getY() > paddle->getY()-ball->getHeight() && paddle->getY()+ball->getHeight() > ball->getY()) {
                if(paddle->getX()-ball->getWidth() <= ball->getX() && ball->getX() < paddle->getX()+paddle->getWidth()+ball->getWidth()) {
                    ball->goingUp = true;
                    if(paddle->getX()-ball->getWidth() <= ball->getX() && ball->getX()+(ball->getWidth()/2) <= paddle->getX()+((paddle->getWidth()/2)/7)*2) {
                        ball->goingLeft = true;
                        ballX = 3;
                    }
                    else if(paddle->getX()+((paddle->getWidth()/2)/7)*2 <= ball->getX()+(ball->getWidth()/2) && ball->getX()+(ball->getWidth()/2) <= paddle->getX()+((paddle->getWidth()/2)/7)*4) {
                        ball->goingLeft = true;
                        ballX = 2;
                    }
                    else if(paddle->getX()+((paddle->getWidth()/2)/7)*4 <= ball->getX()+(ball->getWidth()/2) && ball->getX()+(ball->getWidth()/2) <= paddle->getX()+((paddle->getWidth()/2)/7)*7) {
                        ball->goingLeft = true;
                        ballX = 1;
                    }
                    else if(paddle->getX()+(paddle->getWidth()/2) <= ball->getX()+(ball->getWidth()/2) && ball->getX()+(ball->getWidth()/2) <= paddle->getX()+(paddle->getWidth()/2)+((paddle->getWidth()/2)/7)*3) {
                        ball->goingLeft = false;
                        ballX = 1;
                    }
                    else if(paddle->getX()+(paddle->getWidth()/2)+((paddle->getWidth()/2)/7)*3 <= ball->getX()+(ball->getWidth()/2) && ball->getX()+(ball->getWidth()/2) <= paddle->getX()+(paddle->getWidth()/2)+((paddle->getWidth()/2)/7)*5) {
                        ball->goingLeft = false;
                        ballX = 2;
                    }
                    else if(paddle->getX()+(paddle->getWidth()/2)+((paddle->getWidth()/2)/7)*5 <= ball->getX()+(ball->getWidth()/2) && ball->getX()+(ball->getWidth()/2) <= paddle->getX()+(paddle->getWidth()/2)+((paddle->getWidth()/2)/7)*7) {
                        ball->goingLeft = false;
                        ballX = 3;
                    }
                }
            }
            
            // görs endast efter bollen har skjutits iväg
            if(ball->released) {
                ball->move(ballX, ballY);
            }
            
            
            
            SDL_RenderClear(ren);
            
            // background image
            if(backgroundTexture != nullptr)
                SDL_RenderCopy(ren, backgroundTexture, NULL, NULL);
            
            for (Sprite* s : sprites)
                s->draw();
            
            std::string printpoints = "SCORE: " + std::to_string(totalPoints);
            
            SDL_Surface* rubrSurf = TTF_RenderText_Solid(f, printpoints.c_str(), textColor);
            
            rubrText = SDL_CreateTextureFromSurface(ren, rubrSurf);
            SDL_FreeSurface(rubrSurf);
            rubrRect = { WIDTH-WIDTH+10, HEIGHT-HEIGHT+10, 75, 25 };
            
            SDL_RenderCopy(ren, varvText, NULL, &varvRect);
            SDL_RenderCopy(ren, rubrText, NULL, &rubrRect);
            
            SDL_DestroyTexture(rubrText);
            
            
            SDL_RenderPresent(ren);
        
            // kollar om man vunnit
            int bricksLeft = 0;
            for(BrickSprite* brick : brickField->getBricks()) {
                bricksLeft++;
            }
            if(bricksLeft == 0) {
                gameWon = true;
                goOn = false;
            }
            
            // kollar om man förlorat
            if(ball->getY()-ball->getHeight() > HEIGHT) {
                gameWon = false;
                goOn = false;
            }
            
            if(!SDL_TICKS_PASSED(SDL_GetTicks(), start))
                SDL_Delay(start - SDL_GetTicks());
            
        } // outer while
        SDL_DestroyTexture(varvText);

        return gameWon;
    } // newGame
    
    void GameEngine::highScore() {
        SDL_SetRelativeMouseMode(SDL_FALSE);
        std::string scoreOne = "1: ...", scoreTwo = "2: ...", scoreThree = "3: ...", scoreFour = "4: ...", scoreFive = "5: ...";
        int menuW = 250, menuH = 75, menuX = WIDTH/2-(menuW/2), menuY = (HEIGHT/2)+150;
        
        std::multimap<int, std::string>::iterator it = scores.begin();
        if(scores.size() > 0) {
            scoreOne = "1: " + std::to_string(it->first) + " => " + it->second;
            it++;
        }
        if(scores.size() > 1) {
            scoreTwo = "2: " + std::to_string(it->first) + " => " + it->second;
            it++;
        }
        if(scores.size() > 2) {
            scoreThree = "3: " + std::to_string(it->first) + " => " + it->second;
            it++;
        }
        if(scores.size() > 3) {
            scoreFour = "4: " + std::to_string(it->first) + " => " + it->second;
            it++;
        }
        if(scores.size() > 4) {
            scoreFive = "5: " + std::to_string(it->first) + " => " + it->second;
        }
        
        
        SDL_Surface* firstSurf = TTF_RenderText_Solid(f, scoreOne.c_str(), textColor);
        SDL_Texture* firstTexture = SDL_CreateTextureFromSurface(ren, firstSurf);
        SDL_FreeSurface(firstSurf);
        SDL_Rect firstRect = { (WIDTH/2)-100, 110, 200, 50 };
        
        SDL_Surface* secondSurf = TTF_RenderText_Solid(f, scoreTwo.c_str(), textColor);
        SDL_Texture* secondTexture = SDL_CreateTextureFromSurface(ren, secondSurf);
        SDL_FreeSurface(secondSurf);
        SDL_Rect secondRect = { (WIDTH/2)-100, 170, 200, 50 };
        
        SDL_Surface* thirdSurf = TTF_RenderText_Solid(f, scoreThree.c_str(), textColor);
        SDL_Texture* thirdTexture = SDL_CreateTextureFromSurface(ren, thirdSurf);
        SDL_FreeSurface(thirdSurf);
        SDL_Rect thirdRect = { (WIDTH/2)-100, 230, 200, 50 };
        
        SDL_Surface* fourthSurf = TTF_RenderText_Solid(f, scoreFour.c_str(), textColor);
        SDL_Texture* fourthTexture = SDL_CreateTextureFromSurface(ren, fourthSurf);
        SDL_FreeSurface(fourthSurf);
        SDL_Rect fourthRect = { (WIDTH/2)-100, 290, 200, 50 };
        
        SDL_Surface* fifthSurf = TTF_RenderText_Solid(f, scoreFive.c_str(), textColor);
        SDL_Texture* fifthTexture = SDL_CreateTextureFromSurface(ren, fifthSurf);
        SDL_FreeSurface(fifthSurf);
        SDL_Rect fifthRect = { (WIDTH/2)-100, 360, 200, 50 };
        
        SDL_Surface* menuSurf = IMG_Load("/resources/menu.png");
        SDL_Texture* menuTexture = SDL_CreateTextureFromSurface(ren, menuSurf);
        SDL_FreeSurface(menuSurf);
        SDL_Rect menuRect = { menuX, menuY, menuW, menuH };
        

        bool goOn = true;
        while(goOn) {
            SDL_Event eve;
            while(SDL_PollEvent(&eve)) {
                switch (eve.type) {
                    case SDL_QUIT:
                        goOn = false; break;
                    case SDL_MOUSEBUTTONDOWN:
                        if (eve.button.x >= menuX && eve.button.x <= menuX+menuW && eve.button.y >= menuY && eve.button.y <= menuY + menuH) {
                            goOn = false;
                            break;
                        }
                    case SDL_KEYDOWN:
                        char a = eve.key.keysym.sym;
                        
                        if(nfuncs.count(a)>0) {
                            std::function<void()> nfunk = nfuncs[a];
                            nfunk();
                        }
                } // switch
            } // inner while
            
            SDL_RenderClear(ren);
            
            // background image
            if(backgroundTexture != nullptr)
                SDL_RenderCopy(ren, backgroundTexture, NULL, NULL);
            
            SDL_RenderCopy(ren, firstTexture, NULL, &firstRect);
            SDL_RenderCopy(ren, secondTexture, NULL, &secondRect);
            SDL_RenderCopy(ren, thirdTexture, NULL, &thirdRect);
            SDL_RenderCopy(ren, fourthTexture, NULL, &fourthRect);
            SDL_RenderCopy(ren, fifthTexture, NULL, &fifthRect);
            SDL_RenderCopy(ren, menuTexture, NULL, &menuRect);
            
            SDL_RenderPresent(ren);
            
            
            
        } // outer while
        

        SDL_DestroyTexture(firstTexture);
        SDL_DestroyTexture(secondTexture);
        SDL_DestroyTexture(thirdTexture);
        SDL_DestroyTexture(fourthTexture);
        SDL_DestroyTexture(fifthTexture);
        SDL_DestroyTexture(menuTexture);
        
    } // highscore
    
    
    
    
    bool GameEngine::gameOver() {
        int submitX = 425, submitY = 300, submitW = 250, submitH = 75;
        SDL_SetRelativeMouseMode(SDL_FALSE);
        gameOverInitialized = true;
        int mainMenuW = 250, mainMenuH = 75, mainMenuX = WIDTH/2-(mainMenuW/2), mainMenuY = (HEIGHT/2)+150;
        bool scoreSubmited = false;
        
        // points texture
        std::string printpoints = "Congratulations, you got " + std::to_string(totalPoints) + " points!";
        SDL_Surface* scoreSurf = TTF_RenderText_Solid(f, printpoints.c_str(), textColor);
        SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(ren, scoreSurf);
        SDL_FreeSurface(scoreSurf);
        SDL_Rect scoreRect = { 50, 100, 700, 100 };
        
        std::string enterName = "Enter Name: ";
        SDL_Surface* enterNameSurf = TTF_RenderText_Solid(f, enterName.c_str(), textColor);
        SDL_Texture* enterNameTexture = SDL_CreateTextureFromSurface(ren, enterNameSurf);
        SDL_FreeSurface(enterNameSurf);
        SDL_Rect enterNameRect = { 100, 300, 100, 50 };
        
        SDL_Surface* submitSurf = IMG_Load("/resources/submit.png");
        SDL_Texture* submitTexture = SDL_CreateTextureFromSurface(ren, submitSurf);
        SDL_FreeSurface(submitSurf);
        SDL_Rect submitRect = { submitX, submitY, submitW, submitH };
        
        
        // main menu button
        SDL_Surface* mainMenuSurf = IMG_Load("/resources/menu.png");
        if(mainMenuSurf == NULL)
            std::cout << "Unable to load main menu image" << std::endl;
        SDL_Texture* mainMenuTexture = SDL_CreateTextureFromSurface(ren, mainMenuSurf);
        SDL_FreeSurface(mainMenuSurf);
        SDL_Rect mainMenuRect = { mainMenuX, mainMenuY, mainMenuW, mainMenuH };
        
        // text
        std::string text = "";
        SDL_StartTextInput();
        
        
        bool backToMainMenu = false;
        bool goOn = true;
        while(goOn) {
            SDL_Event eve;
            while (SDL_PollEvent(&eve)) {
                switch (eve.type) {
                    case SDL_QUIT:
                        goOn = false; break;
                    case SDL_MOUSEBUTTONDOWN:
                        if (eve.button.x >= mainMenuX && eve.button.x <= mainMenuX+mainMenuW && eve.button.y >= mainMenuY && eve.button.y <= mainMenuY + mainMenuH) {
                            backToMainMenu = true;
                            goOn = false;
                            break;
                        }
                        else if(eve.button.x >= submitX && eve.button.x <= submitX+submitW && eve.button.y >= submitY && eve.button.y <= submitY + submitH)
                            if(!scoreSubmited) {
                                scores.insert(std::pair<int, std::string>(totalPoints, text));
                                text = "Submited!";
                                scoreSubmited = true;
                            }
                    case SDL_TEXTINPUT:
                        text += eve.text.text;
                        break;
                        
                    case SDL_KEYDOWN:
                        if(eve.key.keysym.sym == SDLK_BACKSPACE && text.length() > 0)
                            text = text.substr(0, text.length() - 1);
                        break;

                } // switch
            } // inner while
            
            SDL_Surface* nameInputSurf = TTF_RenderText_Solid(f, text.c_str(), textColor);
            SDL_Texture* nameInputTexture = SDL_CreateTextureFromSurface(ren, nameInputSurf);
            SDL_FreeSurface(nameInputSurf);
            SDL_Rect nameInputRect = { 210, 300, 200, 50 };
            
            SDL_RenderClear(ren);
            
            // background image
            if(backgroundTexture != nullptr)
                SDL_RenderCopy(ren, backgroundTexture, NULL, NULL);
            
            SDL_RenderCopy(ren, scoreTexture, NULL, &scoreRect);
            SDL_RenderCopy(ren, enterNameTexture, NULL, &enterNameRect);
            SDL_RenderCopy(ren, submitTexture, NULL, &submitRect);
            SDL_RenderCopy(ren, mainMenuTexture, NULL, &mainMenuRect);
            SDL_RenderCopy(ren, nameInputTexture, NULL, &nameInputRect);
            
            SDL_DestroyTexture(nameInputTexture);
            SDL_RenderPresent(ren);
            

            
        } // outer while
        SDL_DestroyTexture(scoreTexture);
        SDL_DestroyTexture(enterNameTexture);
        SDL_DestroyTexture(submitTexture);
        SDL_DestroyTexture(mainMenuTexture);
        return backToMainMenu;
    }
    
    bool GameEngine::run() {
        if(newGame())
            return true;
        else
            return false;
    }
    

    SDL_Renderer* GameEngine::getRen() const {
        return ren;
    }
    
    void GameEngine::reset() {
        if(sprites.size() > 0) {
            std::for_each(sprites.begin(), sprites.end(), [](Sprite* sprite) {
                if(sprite != nullptr)
                    delete sprite;
            });
            
            sprites.clear();
            brickField->getBricks().clear();
            
            if (varvText != nullptr)
                SDL_DestroyTexture(varvText);
        }
    }

    GameEngine::~GameEngine() {
        // if a newGame has been started
        if(newGameInitialized) {
            reset();
        }
        
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        
        delete f;
        
        // if gameOver screen has been displayed
        if(gameOverInitialized) {
            SDL_DestroyTexture(rubrText);
        }
        
        SDL_DestroyTexture(createdByText);
        SDL_DestroyTexture(backgroundTexture);
        TTF_Quit();
        SDL_Quit();
    }

}