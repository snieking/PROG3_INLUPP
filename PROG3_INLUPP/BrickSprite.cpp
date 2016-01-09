#include "BrickSprite.hpp"
#include <iostream>

namespace game {
    BrickSprite::BrickSprite(GameEngine* ge, int x,int y, int w, int h, int p) : Sprite(ge, x, y, w, h) {
        points = p;
    }
    
     bool BrickSprite::intersectsWith(Ball* ball) {
         if(getX() + getWidth()-7 <= ball->getX() && getX() + getWidth()+7 >= ball->getX() && getY()-5 <= ball->getY() && getY()+5 + getHeight() >= ball->getY()) {
             ball->goingLeft = false;
             return true;
         }
         
         else if(getX()-7 <= ball->getX() + ball->getWidth() && getX()+7 >= ball->getX() + ball->getWidth() && getY()-7 <= ball->getY() && getY()+7 + getHeight() >= ball->getY()) {
             ball->goingLeft = true;
             return true;
         }
         
         else if(getY() + getHeight()-7 <= ball->getY() && getY() + getHeight()+7 >= ball->getY() && getX()-7 <= ball->getX() && getX()+7 + getWidth() >= ball->getX() + ball->getWidth()) {
             ball->goingUp = false;
             return true;
         }
         
         else if(getY()-7 <= ball->getY() + ball->getHeight() && getY()+7 >= ball->getY() + ball->getHeight() && getX()-7 <= ball->getX() && getX()+7 + getWidth() >= ball->getX() + ball->getWidth()) {
             ball->goingUp = true;
             return true;
         }
         
         else
             return false;
     }

    BrickSprite::~BrickSprite() {}
}
