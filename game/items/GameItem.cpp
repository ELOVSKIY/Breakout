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

GameItem::GameItem(const int left,
                   const int top,
                   const int width,
                   const int height) {
    this->left = left;
    this->top = top;
    this->width = width;
    this->height = height;
}
