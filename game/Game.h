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
    HWND hWnd;

    measure width;
    measure height;

    bool active;

    Plate *plate;
    list<Brick *> *bricks;
    Ball *ball;
    list<GameItem *> *gameItems;
public:
    Game(HWND hWnd,
         const int width,
         const int height);

//    void Initialize();

    void Click();

    measure GetMaxAvailableDistance(const GameItem *gameItem,
                                    const Vector vector);

    measure GetMaxAvailableDistance(const GameItem *gameItem,
                                    const Vector vector,
                                    const measure maxAvailableDistance);

    measure GetMinGameItemMeasure();

    bool IsBetweenHorizontalEdge(const measure yPos);

    bool IsBetweenVerticalEdge(const measure xPos);

    void Draw(HWND hWnd);

    void GetInput(HWND hWnd,
                  UINT uMsg,
                  WPARAM wParam,
                  LPARAM lParam);
};


#endif //BREAKOUT_GAME_H
