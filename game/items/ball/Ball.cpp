#include "Ball.h"

void Ball::Draw(HDC &hdc) {
    HBRUSH hbrush = CreateSolidBrush(RGB(0, 200, 50));
    SelectObject(hdc, hbrush);
    Ellipse(hdc, left, top, left + width, top + height);
    DeleteObject(hbrush);
}

Ball::Ball(int left, int top, int radius) : GameItem(left, top, radius, radius){

}
