//
// Created by Helicoptera on 17.10.2020.
//

#ifndef BREAKOUT_GAMEITEM_H
#define BREAKOUT_GAMEITEM_H


#include <Windows.h>

class GameItem {
public:
    virtual void Draw(HDC &hdc);
    GameItem(int left, int top, int width, int height);
protected:
    int width;
    int height;
    int left;
    int top;
    int right;
    int bottom;
};


#endif //BREAKOUT_GAMEITEM_H
