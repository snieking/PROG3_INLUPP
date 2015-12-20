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
    void addHighScoreShortcut(char c);
    SDL_Renderer* getRen() const; // borde vara privat egentligen(?)
    bool run();
    bool mainMenu();
    bool newGame();
    void highScore();
    bool gameOver();
    void setPaddle(PlayerSprite* thePaddle);
    void setBall(Ball* theBall);
    void setBrickField(BrickField* theBrickField);
    BrickField* getBrickField();
    int totalPoints = 0;
    ~GameEngine();
private:
    friend class Sprite;
    SDL_Window* win;
    SDL_Renderer* ren;
    std::list<Sprite*> sprites;
    
    std::map<char, mfunk> functions;
    PlayerSprite* paddle;
    Ball* ball;
    BrickField* brickField;
    const int timePerFrame = 5;
    int WIDTH, HEIGHT;
    SDL_Color textColor;
    TTF_Font* f;
    SDL_Rect rubrRect;
    SDL_Rect createdByRect;
    SDL_Texture* rubrText;
    SDL_Texture* createdByText;
    SDL_Texture* newGameTexture;
    SDL_Texture* highscoreTexture;
    
    /* main Menu */
    
    /* high Score */
    std::multimap<int, std::string, std::greater<int>> scores;
    
    /* new Game */
    bool newGameInitialized = false;
    SDL_Texture* varvText;
    SDL_Rect varvRect;
    
    /* game Over */
    bool gameOverInitialized = false;
};
    
}

#endif /* GameEngine_hpp */
