#include "MovingSprite.hpp"

namespace game {
    MovingSprite::MovingSprite(GameEngine* ge, int x, int y, int w, int h) : Sprite(ge, x, y, w, h) {}
    
    MovingSprite::~MovingSprite() {}
}