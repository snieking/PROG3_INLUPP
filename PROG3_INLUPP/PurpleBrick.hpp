//
//  PurpleBrick.hpp
//  PROG3_INLUPP
//
//  Created by Viktor Plane on 19/12/15.
//  Copyright © 2015 Viktor Plane. All rights reserved.
//

#ifndef PurpleBrick_hpp
#define PurpleBrick_hpp

#include <stdio.h>
#include "BrickSprite.hpp"

namespace game {
    class PurpleBrick : public BrickSprite {
    public:
        void draw();
        static PurpleBrick* getInstance(GameEngine* ge, int x, int y, int w, int h, int points);
        ~PurpleBrick();
    protected:
        PurpleBrick(GameEngine* ge, int x, int y, int w, int h, int points);
    private:
        PurpleBrick(const PurpleBrick&) = delete;
        const PurpleBrick& operator=(const PurpleBrick&) = delete;
        SDL_Texture* ture;
    };
}
#endif /* PurpleBrick_hpp */
