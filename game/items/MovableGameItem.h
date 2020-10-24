//
// Created by avter on 22.10.2020.
//

#ifndef BREAKOUT_MOVABLEGAMEITEM_H
#define BREAKOUT_MOVABLEGAMEITEM_H

#include "GameItem.h"
#include <set>

enum Direction {
    POSITIVE = 1,
    NEGATIVE = -1
};

#define POSITIVE_DIRECTION 1
#define NEGATIVE_DIRECTION -1

typedef struct Velocity {
    char direction;
    measure value;
} Velocity;

typedef struct Vector {
    Velocity xVector;
    Velocity yVector;
} Vector;


class MovableGameItem : public GameItem {
    measure speed;
public:
    MovableGameItem(int left,
                    int top,
                    int width,
                    int height,
                    int speed);

    measure GetSpeed();

    virtual void Move();

    virtual void Move(const Vector vector);
};


#endif //BREAKOUT_MOVABLEGAMEITEM_H
