#ifndef GameEngine_hpp
#define GameEngine_hpp

#include <string>
#include <SDL2/SDL.h>
#include <list>
#include <map>
#include "Sprite.hpp"
#include "PlayerSprite.hpp"
#include "Ball.hpp"
#include "BrickField.hpp"
#include "SDL2_ttf/SDL_ttf.h"


namespace game {
typedef void (GameEngine::*mfunk)();

class Sprite;

class GameEngine {
public:
    GameEngine(std::string title, int x, int y, int w, int h);
    void add(Sprite* sprite);
    void remove(Sprite* sprite);
    std::list<Sprite*>& getSprites() { return sprites; }
    void addShortcut(char c, mfunk f);
    void addNShortcut(char c, std::function<void()> nf);
    SDL_Renderer* getRen() const;
    std::string getDifficulty() const { return std::to_string(timePerFrame); }
    void setBackgroundPath(std::string s) { backgroundPath = s; }
    void plusDifficulty();
    void minusDifficulty() { timePerFrame++; }
    bool run();
    bool mainMenu();
    bool newGame();
    void highScore();
    bool gameOver();
    void setPaddle(PlayerSprite* thePaddle);
    void setBall(Ball* theBall);
    void setBrickField(BrickField* theBrickField);
    BrickField* getBrickField();
    int totalPoints = 0; // Okej att ha publik? Känns onödigt att göra set och get för den...
    void reset();
    ~GameEngine();
private:
    friend class Sprite;
    
    /* Global */
    SDL_Window* win;
    SDL_Renderer* ren;
    std::list<Sprite*> sprites;
    std::map<char, mfunk> functions;
    std::map<char, std::function<void()>> nfuncs;
    
    int timePerFrame = 3;
    int WIDTH, HEIGHT;
    std::string backgroundPath;
    SDL_Texture* backgroundTexture;
    SDL_Color textColor;
    TTF_Font* f;
    PlayerSprite* paddle;
    Ball* ball;
    BrickField* brickField;
    
    /* Main Menu */
    SDL_Texture* plusMinusText;
    SDL_Texture* difficultyText;
    SDL_Texture* createdByText;
    SDL_Texture* newGameTexture;
    SDL_Texture* highscoreTexture;
    SDL_Rect createdByRect;
    
    /* Highscore */
    std::multimap<int, std::string, std::greater<int>> scores;
    
    /* New Game */
    bool newGameInitialized = false;
    SDL_Texture* varvText;
    SDL_Rect varvRect;
    SDL_Texture* rubrText;
    SDL_Rect rubrRect;
    bool brickRemoved;
    bool willStartGame;
    bool gameWon;
    
    /* Game Over */
    bool gameOverInitialized = false;
};
    
}

#endif /* GameEngine_hpp */
