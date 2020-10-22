//
// Created by avter on 22.10.2020.
//

#include "MovableGameItem.h"

MovableGameItem::MovableGameItem(int left, int top, int width, int height, int speed) :
        GameItem(left, top, width, height) {
}


void MovableGameItem::move(std::set<Direction> directions) {
    for (auto direction : directions) {
        switch (direction) {
            case TOP:
                this->top - speed;
                break;
            case RIGHT:
                this->left + speed;
                break;
            case LEFT:
                this->left - speed;
                break;
                this->top + speed;
            case BOTTOM:
                break;
        }
    }
}

void MovableGameItem::move() {
    // do nothing
}
