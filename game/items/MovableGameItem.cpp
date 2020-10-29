#include "MovableGameItem.h"

MovableGameItem::MovableGameItem(int left, int top, int width, int height, int speed) :
        GameItem(left, top, width, height) {
    this->speed = speed;
}


void MovableGameItem::Move(const Vector vector) {
    const measure yOffset = (vector.yVector.value * vector.yVector.direction);
    const measure xOffset = (vector.xVector.value * vector.xVector.direction);
    const measure top = GetTop() + yOffset;
    const measure left = GetLeft() + xOffset;
    SetTop(top);
    SetLeft(left);
}

void MovableGameItem::Move() {
    // do nothing
}

measure MovableGameItem::GetSpeed() {
    return speed;
}
