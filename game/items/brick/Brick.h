//
// Created by Helicoptera on 17.10.2020.
//

#ifndef BREAKOUT_BRICK_H
#define BREAKOUT_BRICK_H

#include "../GameItem.h"

class Brick : public GameItem {
private:
    COLORREF colorRef;
public:
    void Draw(HDC &hdc) override;

    Brick(int left, int top, int width, int height, int colorIndex, int lineCount);
};


#endif //BREAKOUT_BRICK_H
