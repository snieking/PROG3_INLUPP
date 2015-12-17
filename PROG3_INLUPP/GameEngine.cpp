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
        f = TTF_OpenFont("/Library/Fonts/Arial Black.ttf", 100);
        textColor = {255, 255, 255};
    }
    
    void GameEngine::add(Sprite *sprite) {
        sprites.push_back(sprite);
    }
    
    void GameEngine::remove(Sprite *sprite) {
        auto pos = find(sprites.begin(), sprites.end(), sprite);
        std::cout << "Innan sprites: " << sprites.size() << std::endl;
        sprites.erase(pos);
        delete sprite;
        std::cout << "Efter sprites: " << sprites.size() << std::endl;
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
        
        // New game button
        SDL_Surface* newGameSurf = IMG_Load("/Users/viktorplane/Dropbox/game/new/playGame.png");
        if(newGameSurf == NULL)
            std::cout << "Unable to load image" << std::endl;
        newGameTexture = SDL_CreateTextureFromSurface(ren, newGameSurf);
        SDL_FreeSurface(newGameSurf);
        SDL_Rect newGameRect = { newGameX, newGameY, newGameW, newGameH };
        
        // Highscore button
        SDL_Surface* highscoreSurf = IMG_Load("/Users/viktorplane/Dropbox/game/new/scores.png");
        if(highscoreSurf == NULL)
            std::cout << "Unable to load image" << std::endl;
        
        highscoreTexture = SDL_CreateTextureFromSurface(ren, highscoreSurf);
        SDL_FreeSurface(highscoreSurf);
        SDL_Rect highscoreRect = { highscoreX, highscoreY, highscoreW, highscoreH };
        
        // Created by text
        std::string createdBy = "Viktor Plane and Olof Hofstedt (PROG3 2015/16)";
        SDL_Surface* createdBySurf = TTF_RenderText_Solid(f, createdBy.c_str(), textColor);
        createdByText = SDL_CreateTextureFromSurface(ren, createdBySurf);
        SDL_FreeSurface(createdBySurf);
        createdByRect = { WIDTH - (WIDTH/2)-10, HEIGHT-25, WIDTH/2, 20 };
        
        // goOn
        bool goOn = true;
        while(goOn) {
            SDL_Event eve;
            while(SDL_PollEvent(&eve)) {
                switch (eve.type) {
                    case SDL_QUIT:
                        goOn = false; break;
                    case SDL_MOUSEBUTTONDOWN:
                        if (eve.button.x >= newGameX && eve.button.x <= newGameX+newGameW && eve.button.y >= newGameY && eve.button.y <= newGameY+newGameH) {
                            return true;
                            break;
                        }
                        if (eve.button.x >= highscoreX && eve.button.x <= highscoreX+highscoreW && eve.button.y >= highscoreY && eve.button.y <= highscoreY+highscoreH) {
                            highScore();
                        }
                        
                } // switch
            } // inner-while
            
            SDL_RenderClear(ren);
            SDL_RenderCopy(ren, newGameTexture, NULL, &newGameRect);
            SDL_RenderCopy(ren, highscoreTexture, NULL, &highscoreRect);
            SDL_RenderCopy(ren, createdByText, NULL, &createdByRect);
            SDL_RenderPresent(ren);
        } // outer-while
        return false;
    } // mainMenu
    
    bool GameEngine::newGame() {
        // Removes mouse
        SDL_SetRelativeMouseMode(SDL_TRUE);
        
        newGameInitialized = true;

        int x = 0;
        int ballY = 1, ballX = 0;
        //SDL_RenderClear(ren);
        //SDL_RenderPresent(ren);
        for (Sprite* s : sprites)
            s->draw();
        
        ball->goingLeft = true;
        SDL_RenderPresent(ren);
        bool goOn = true;
        while (goOn) {
            Uint32 start = SDL_GetTicks() + FPS;
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
                } // switch
            } // inre while
            
            
            // Ifall bollen träffar taket så går den inte upp längre
            if(ball->getY() == 0)
                ball->goingUp = false;
            
            for(Brick* brick: brickField->getBricks()) {
                if(!brick->hit)
                    if(brick->intersectsWith(ball)) {
                        brick->hit = true;
                        totalPoints += brick->points;
                        //std::cout << "Tog just bort en" << std::endl;
                        if((brick->getX() + brick->getWidth() == ball->getX())) {
                            //std::cout << "Högerkanten" << std::endl;
                            ball->goingLeft = false;
                        }
                        else if(brick->getX() == ball->getX() + ball->getWidth()) {
                            ball->goingLeft = true;
                            //std::cout << "Vänsterkanten" << std::endl;
                        }
                        else if(brick->getY() + brick->getHeight() == ball->getY()) {
                            ball->goingUp = false;
                            brickField->remove(brick);
                            std::cout << "tar bort" << std::endl;
                            remove(brick);
                            //std::cout << "Underkanten" << std::endl;
                        }
                        else if((brick->getY() == ball->getY() + ball->getHeight())) {
                            ball->goingUp = true;
                            //std::cout << "Överkanten" << std::endl;
                        }
                    }
            }
            
            // Kolla ifall bollen har träffat en vägg
            if(ball->getX() <= 0)
                ball->goingLeft = false;
            if(ball->getX()+ball->getWidth() >= 800)
                ball->goingLeft = true;
            
            // Bollen ändras till goingUp efter att den 'studsat' på paddeln
            if(ball->getY() > paddle->getY()-10 && paddle->getY()+10 > ball->getY()) {
                // -10 så att den träffar på vänstersida
                if(paddle->getX()-ball->getWidth() <= ball->getX() && ball->getX() < paddle->getX()+paddle->getWidth()+ball->getWidth()) {
                    ball->goingUp = true;
                    if(paddle->getX()-ball->getWidth() <= ball->getX() && ball->getX() <= paddle->getX()+ball->getWidth()) {
                        ball->goingLeft = true;
                        ballX = 2;
                    }
                    else if(paddle->getX()+ball->getWidth() <= ball->getX() && ball->getX() <= paddle->getX()+(paddle->getWidth()/2)) {
                        ball->goingLeft = true;
                        ballX = 1;
                    }
                    else if(paddle->getX()+(paddle->getWidth()/2) <= ball->getX() && ball->getX() <= paddle->getX()+(paddle->getWidth()/2)+ball->getWidth()) {
                        ball->goingLeft = false;
                        ballX = 1;
                    }
                    else {
                        ball->goingLeft = false;
                        ballX = 2;
                    }
                }
            }
            
            // Görs endast efter bollen har skjutits iväg
            if(ball->released) {
                ball->move(ballX, ballY);
            }
            
            // Kollar om man vunnit
            int bricksLeft = 0;
            for(Brick* brick : brickField->getBricks()) {
                if(!brick->hit)
                    bricksLeft++;
            }
            if(bricksLeft == 0) {
                return true;
            }
            
            // Kollar om man förlorat
            if(ball->getY()-ball->getHeight() > HEIGHT) {
                return false;
            }
            
            SDL_RenderClear(ren);
            for (Sprite* s : sprites)
                s->draw();
            
            std::string printpoints = "Score: " + std::to_string(totalPoints);
            
            SDL_Surface* rubrSurf = TTF_RenderText_Solid(f, printpoints.c_str(), textColor);
            
            rubrText = SDL_CreateTextureFromSurface(ren, rubrSurf);
            SDL_FreeSurface(rubrSurf);
            rubrRect = { WIDTH-WIDTH, HEIGHT-HEIGHT, 75, 50 };

            SDL_RenderCopy(ren, rubrText, NULL, &rubrRect);
            
            SDL_DestroyTexture(rubrText);
            
            SDL_RenderPresent(ren);
            
            //std::cout << SDL_TICKS_PASSED(SDL_GetTicks(), start) << std::endl;
            
            if(!SDL_TICKS_PASSED(SDL_GetTicks(), start))
                SDL_Delay(start - SDL_GetTicks());
            
        } // yttre while
        return false;
    } // newGame
    
    void GameEngine::highScore() {
        SDL_SetRelativeMouseMode(SDL_FALSE);
        std::string scoreOne = "1: ...", scoreTwo = "2: ...", scoreThree = "3: ...", scoreFour = "4: ...", scoreFive = "5: ...";
        int menuW = 250, menuH = 75, menuX = WIDTH/2-(menuW/2), menuY = (HEIGHT/2)+150;
        
        std::multimap<int, std::string>::iterator it = scores.begin();
        if(scores.size() > 0) {
            scoreOne = "1: " + std::to_string(it->first) + " => " + it->second;
            std::cout << scoreOne << std::endl;
            it++;
        }
        if(scores.size() > 1) {
            scoreTwo = "2: " + std::to_string(it->first) + " => " + it->second;
            std::cout << scoreTwo << std::endl;
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
            it++;
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
        
        SDL_Surface* menuSurf = IMG_Load("/Users/viktorplane/Dropbox/game/new/menu.png");
        SDL_Texture* menuTexture = SDL_CreateTextureFromSurface(ren, menuSurf);
        SDL_FreeSurface(menuSurf);
        SDL_Rect menuRect = { menuX, menuY, menuW, menuH };
        
        
        // goOn
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
                    
                        
                } // switch
            } // inner-while
            
            SDL_RenderClear(ren);
            
            SDL_RenderCopy(ren, firstTexture, NULL, &firstRect);
            SDL_RenderCopy(ren, secondTexture, NULL, &secondRect);
            SDL_RenderCopy(ren, thirdTexture, NULL, &thirdRect);
            SDL_RenderCopy(ren, fourthTexture, NULL, &fourthRect);
            SDL_RenderCopy(ren, fifthTexture, NULL, &fifthRect);
            SDL_RenderCopy(ren, menuTexture, NULL, &menuRect);
            
            SDL_RenderPresent(ren);
            
        } // outer-while
        
        
        
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
        
        // Points texture
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
        
        SDL_Surface* submitSurf = IMG_Load("/Users/viktorplane/Dropbox/game/new/submit.png");
        SDL_Texture* submitTexture = SDL_CreateTextureFromSurface(ren, submitSurf);
        SDL_FreeSurface(submitSurf);
        SDL_Rect submitRect = { submitX, submitY, submitW, submitH };
        
        
        // Main menu button
        SDL_Surface* mainMenuSurf = IMG_Load("/Users/viktorplane/Dropbox/game/new/menu.png");
        if(mainMenuSurf == NULL)
            std::cout << "Unable to load main menu image" << std::endl;
        SDL_Texture* mainMenuTexture = SDL_CreateTextureFromSurface(ren, mainMenuSurf);
        SDL_FreeSurface(mainMenuSurf);
        SDL_Rect mainMenuRect = { mainMenuX, mainMenuY, mainMenuW, mainMenuH };
        
        // text
        std::string text = "";
        SDL_StartTextInput();
        
        // goOn
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
            } // inner-while
            
            SDL_Surface* nameInputSurf = TTF_RenderText_Solid(f, text.c_str(), textColor);
            SDL_Texture* nameInputTexture = SDL_CreateTextureFromSurface(ren, nameInputSurf);
            SDL_FreeSurface(nameInputSurf);
            SDL_Rect nameInputRect = { 210, 300, 200, 50 };
            
            SDL_RenderClear(ren);
            SDL_RenderCopy(ren, scoreTexture, NULL, &scoreRect);
            SDL_RenderCopy(ren, enterNameTexture, NULL, &enterNameRect);
            SDL_RenderCopy(ren, submitTexture, NULL, &submitRect);
            SDL_RenderCopy(ren, mainMenuTexture, NULL, &mainMenuRect);
            SDL_RenderCopy(ren, nameInputTexture, NULL, &nameInputRect);
            SDL_DestroyTexture(nameInputTexture);
            SDL_RenderPresent(ren);
            
        } // outer-while
        
        SDL_StopTextInput();
        SDL_DestroyTexture(submitTexture);
        SDL_DestroyTexture(enterNameTexture);
        SDL_DestroyTexture(mainMenuTexture);
        SDL_DestroyTexture(scoreTexture);
        
        return backToMainMenu;
    }
    
    bool GameEngine::run() {
        if(newGame())
            return true;
        else
            return false;
    } // run
    

    SDL_Renderer* GameEngine::getRen() const {
        return ren;
    }

    GameEngine::~GameEngine() {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        if(f != NULL)
            delete f;
        
        if(newGameInitialized) {
            for(Brick* brick : brickField->getBricks())
                delete brick;
            
            for(Sprite* sprite : sprites)
                delete sprite;
            
            delete paddle;
            delete ball;
            delete brickField;
        }
        
        if(gameOverInitialized) {
            SDL_DestroyTexture(rubrText);
        }
        
        SDL_DestroyTexture(createdByText);
        TTF_Quit();
    }

}