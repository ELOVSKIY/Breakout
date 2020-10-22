//
// Created by avter on 22.10.2020.
//

#ifndef BREAKOUT_MOVABLEGAMEITEM_H
#define BREAKOUT_MOVABLEGAMEITEM_H

#include "GameItem.h"
#include <set>

enum Direction {
    TOP = 1,
    RIGHT = 2,
    BOTTOM = -1,
    LEFT = -2
};

class MovableGameItem : public GameItem {
protected:
    int speed;
public:
    MovableGameItem(int left, int top, int width, int height, int speed);

    virtual void move();

    virtual void move(std::set<Direction> directions);
};


#endif //BREAKOUT_MOVABLEGAMEITEM_H
