#include "BrickSprite.hpp"
#include <iostream>

namespace game {
    BrickSprite::BrickSprite(GameEngine* ge, int x,int y, int w, int h, int p) : Sprite(ge, x, y, w, h) {
        points = p;
    }
    
     bool BrickSprite::intersectsWith(Ball* ball) {
         if(getX() + getWidth()-5 <= ball->getX() && getX() + getWidth()+5 >= ball->getX() && getY()-5 <= ball->getY() && getY()+5 + getHeight() >= ball->getY()) {
             ball->goingLeft = false;
             return true;
         }
         
         else if(getX()-5 <= ball->getX() + ball->getWidth() && getX()+5 >= ball->getX() + ball->getWidth() && getY()-5 <= ball->getY() && getY()+5 + getHeight() >= ball->getY()) {
             ball->goingLeft = true;
             return true;
         }
         
         else if(getY() + getHeight()-5 <= ball->getY() && getY() + getHeight()+5 >= ball->getY() && getX()-5 <= ball->getX() && getX()+5 + getWidth() >= ball->getX() + ball->getWidth()) {
             ball->goingUp = false;
             return true;
         }
         
         else if(getY()-5 <= ball->getY() + ball->getHeight() && getY()+5 >= ball->getY() + ball->getHeight() && getX()-5 <= ball->getX() && getX()+5 + getWidth() >= ball->getX() + ball->getWidth()) {
             ball->goingUp = true;
             return true;
         }
         
         else
             return false;
     }

    BrickSprite::~BrickSprite() {}
}
