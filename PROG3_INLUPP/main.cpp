//
//  main.cpp
//  PROG3_INLUPP
//
//  Created by Viktor Plane on 04/12/15.
//  Copyright © 2015 Viktor Plane. All rights reserved.
//

#include "GameEngine.hpp"

#include <stdexcept>
#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

int main(int argc, const char * argv[]) {
    try {
        GameEngine* ge = new GameEngine("Best Game Ever", 200, 200, 500, 600);
        
        ge->run();
        
        delete(ge);
    } catch (runtime_error& e) {
        cerr << e.what() << endl;
    }
    return 0;
}
