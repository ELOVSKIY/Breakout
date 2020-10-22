#ifndef BREAKOUT_PLATE_H
#define BREAKOUT_PLATE_H


#include "../MovableGameItem.h"

class Plate : public MovableGameItem {
public:

    Plate(int left, int top, int width, int height, int speed);

    void Draw(HDC &hdc) override;

};


#endif //BREAKOUT_PLATE_H
