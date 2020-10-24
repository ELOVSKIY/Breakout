//
// Created by Helicoptera on 17.10.2020.
//

#include "GameItem.h"

void GameItem::Draw(HDC &hdc) {
//    HBRUSH hbrush;
//    hbrush = CreateSolidBrush();
//    SelectObject(hdc, hbrush);
//    float x = 0;
//    float y = 0;
//    getCoordinate(&x, &y, atom.angle, atom.rad);
//    float left = x + WINDOW_WIDTH/2 - ATOM_DIAMETER / 2;
//    float top = y + WINDOW_HEIGHT/2 - ATOM_DIAMETER / 2;
//    float right = left + ATOM_DIAMETER;
//    float bottom = top + ATOM_DIAMETER;
//    Ellipse(hdc, left, top, left + width, top + height);
    Rectangle(hdc, 200, 200, 500, 500);
//    FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
//    DeleteObject(hbrush);
}

GameItem::GameItem(int left,
                   int top,
                   int width,
                   int height) {
    this->left = left;
    this->top = top;
    this->width = width;
    this->height = height;
    this->right = left + width;
    this->bottom = top + height;
}

measure GameItem::GetWidth() const {
    return width;
}

measure GameItem::GetHeight() const {
    return height;
}

measure GameItem::GetLeft() const {
    return left;
}

measure GameItem::GetTop() const {
    return top;
}

measure GameItem::GetRight() const {
    return left + width;
}

measure GameItem::GetBottom() const {
    return top + height;
}

void GameItem::SetLeft(int left) {
    this->left = left;
    this->right = left + width;
}

void GameItem::SetTop(int top) {
    this->top = top;
    this->bottom = top + height;
}

Border GameItem::GetBorder() const {
    Border gameItemBorder {top, right, bottom, left};
    return gameItemBorder;
}
