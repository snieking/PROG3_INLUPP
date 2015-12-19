//
//  GoldBrick.hpp
//  PROG3_INLUPP
//
//  Created by Viktor Plane on 19/12/15.
//  Copyright © 2015 Viktor Plane. All rights reserved.
//

#ifndef GoldBrick_hpp
#define GoldBrick_hpp

#include <stdio.h>
#include "BrickSprite.hpp"

namespace game {
    class GoldBrick : public BrickSprite {
    public:
        void draw();
        static GoldBrick* getInstance(GameEngine* ge, int x, int y, int w, int h, int points);
        ~GoldBrick();
    protected:
        GoldBrick(GameEngine* ge, int x, int y, int w, int h, int points);
    private:
        GoldBrick(const GoldBrick&) = delete;
        const GoldBrick& operator=(const GoldBrick&) = delete;
        SDL_Texture* ture;
    };
}

#endif /* GoldBrick_hpp */
