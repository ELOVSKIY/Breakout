#include "Plate.h"

Plate::Plate(const int left,
             const int top,
             const int width,
             const int height,
             const int speed) : MovableGameItem(left, top, width, height, speed){

}

void Plate::Draw(HDC &hdc) {
    HBRUSH hbrush = CreateSolidBrush(RGB(234, 0, 91));
    SelectObject(hdc, hbrush);
    Rectangle(hdc, this->left, this->top, this->left + this->width, this->top + this->height);
    DeleteObject(hbrush);
}
