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

    void Initialize();

    void StartGame();

    void GameOver();

    void Click();

    float GetAvailableVectorPercent(const GameItem *gameItem,
                                    Vector &vector);

//    float GetAvailableVectorPercent(const GameItem *gameItem,
//                                    Vector &vector,
//                                    const measure maxAvailableDistance);

    measure GetMinGameItemMeasure();

    GameItem *GetNearestGameItem(const GameItem *movableGameItem,
                                 Vector &vector,
                                 const measure xCenterPos,
                                 const measure yCenterPos) const;

    void Draw(HWND hWnd);

    void GetInput(HWND hWnd,
                  UINT uMsg,
                  WPARAM wParam,
                  LPARAM lParam);
};


#endif //BREAKOUT_GAME_H
