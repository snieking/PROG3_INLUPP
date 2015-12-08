//
//  Board.hpp
//  PROG3_INLUPP
//
//  Created by Viktor Plane on 08/12/15.
//  Copyright © 2015 Viktor Plane. All rights reserved.
//

#ifndef Board_hpp
#define Board_hpp

#include "Sprite.hpp"
#include <stdlib.h>
#include <time.h>

// Define the dimensions of the board and bricks
#define BOARD_WIDTH 12
#define BOARD_HEIGHT 12
#define BOARD_BRWIDTH 64
#define BOARD_BRHEIGHT 24

namespace game {

    class Brick {
    public:
        int type;
        bool state;
    };

    class Board: public Sprite {
    public:
    private:
    };
}

#endif /* Board_hpp */
