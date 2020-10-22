//
// Created by Helicoptera on 17.10.2020.
//

#ifndef BREAKOUT_BALL_H
#define BREAKOUT_BALL_H

#include "../GameItem.h"

//class SpeedDirection {
//private:
//    int horizontalDirection;
//    int verticalDirection;
//public:
//    int getHorizontalDirection();
//    int getVerticalDirection();
//};

class Ball : GameItem {
private:
    int speed;
//    SpeedDirection speedDirection;
public:
//    void move();
    void Draw(HDC &hdc) override;
    Ball(int left, int top, int radius);
};


#endif //BREAKOUT_BALL_H
