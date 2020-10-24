//
// Created by avter on 22.10.2020.
//

#include "MovableGameItem.h"

MovableGameItem::MovableGameItem(int left, int top, int width, int height, int speed) :
        GameItem(left, top, width, height) {
    this->speed = speed;
}


void MovableGameItem::Move(const Vector vector) {
    const measure top = GetTop() + (vector.yVector.value * vector.yVector.direction);
    const measure left = GetLeft() + (vector.xVector.value * vector.xVector.direction);
    SetTop(top);
    SetLeft(left);
}

void MovableGameItem::Move() {
    // do nothing
}

measure MovableGameItem::GetSpeed() {
    return speed;
}
