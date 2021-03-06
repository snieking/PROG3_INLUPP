#include "Sprite.hpp"
#include "GameEngine.hpp"

namespace game {

    Sprite::Sprite(GameEngine* ge, int x, int y, int w, int h) :win(ge), rect { x,y,w,h } {
        ge->add(this);
    }
    
    void Sprite::setX(int newX) {
        rect.x = newX;
    }
    
}
