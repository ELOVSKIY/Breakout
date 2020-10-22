//
// Created by Helicoptera on 17.10.2020.
//

#ifndef BREAKOUT_GAME_H
#define BREAKOUT_GAME_H

#include "items/plate/Plate.h"
#include "items/brick/Brick.h"
#include "items/ball/Ball.h"
#include <list>

using namespace std;

class Game {
private:
    Plate *plate;
    list<Brick*> *bricks;
    Ball *ball;
public:
    Game(int width, int height);
    void Initialize();
    void Draw(HDC wHdc);
    void GetInput(UINT uMsg,
                  WPARAM wParam,
                  LPARAM lParam);
};


#endif //BREAKOUT_GAME_H
