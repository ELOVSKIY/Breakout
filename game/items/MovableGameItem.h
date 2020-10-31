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
    measure direction;
    measure value;
} Velocity;

typedef struct Vector {
    Velocity xVector;
    Velocity yVector;

public:
    Vector operator*(const float value) {
        const float absValue = abs(value);
        const float sign = value / absValue;
        Vector vector = {{xVector.direction * sign, xVector.value * absValue},
                         {yVector.direction * sign, yVector.value * absValue}};
        return vector;
    }

    void ChangeVerticalDirection() {
        yVector.direction = -yVector.direction;
    }

    void ChangeHorizontalDirection() {
        xVector.direction = -xVector.direction;
    }
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
