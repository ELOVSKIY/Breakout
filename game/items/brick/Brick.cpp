//
// Created by Helicoptera on 17.10.2020.
//
#include "Brick.h"

Brick::Brick(int left,
             int top,
             int width,
             int height,
             int colorIndex,
             int lineCount) : GameItem(left, top, width, height) {
    const float intensity = 256.0F;
    COLORREF red = (float) (10 - colorIndex) / (float) lineCount * intensity;
    COLORREF green = (float) abs(5 - colorIndex) / (float) lineCount * intensity;
    COLORREF blue = (float) colorIndex / (float) lineCount * intensity;
    this->colorRef = RGB(red, green, blue);
}

void Brick::Draw(HDC &hdc) {
    HBRUSH hbrush = CreateSolidBrush(this->colorRef);
    SelectObject(hdc, hbrush);
    Rectangle(hdc, this->left, this->top, this->left + this->width, this->top + this->height);
    DeleteObject(hbrush);
}
