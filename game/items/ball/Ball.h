#ifndef BREAKOUT_BALL_H
#define BREAKOUT_BALL_H

#include "../MovableGameItem.h"

class Ball : public MovableGameItem{
private:
    Vector vector;
public:
    Ball(const int left,
         const int top,
         const int radius,
         const measure speed);

    void Draw(HDC &hdc) override;

    void InverseHorizontal();

    void InverseVertical();

    Vector &GetVector();

};


#endif //BREAKOUT_BALL_H
