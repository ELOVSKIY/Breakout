#include "Ball.h"

Ball::Ball(const int left,
           const int top,
           const int radius,
           const measure speed) : MovableGameItem(left, top, radius, radius, speed) {
    const measure xSpeed = speed * 1;
    const measure ySpeed = speed * 1.5;
    vector = {{1,  xSpeed},
              {-1, ySpeed}};
}


void Ball::Draw(HDC &hdc) {
    HBRUSH hbrush = CreateSolidBrush(RGB(140, 50, 200));
    SelectObject(hdc, hbrush);
    Ellipse(hdc, GetLeft(), GetTop(), GetRight(), GetBottom());
    DeleteObject(hbrush);
//
//    Graphics graphics(hdc);
//    Gdiplus::LinearGradientBrush linGrBrush(
//            Point(0, 10),
//            Point(200, 10),
//            Color(255, 255, 0, 0),   // opaque red
//            Color(255, 0, 0, 255));  // opaque blue
//
//    Pen pen(&linGrBrush);
//
//    graphics.DrawLine(&pen, 0, 10, 200, 10);
//    graphics.FillEllipse(&linGrBrush, 0, 30, 200, 100);
//    graphics.FillRectangle(&linGrBrush, 0, 155, 500, 30);

}

void Ball::InverseHorizontal() {
    vector.xVector.direction = -vector.xVector.direction;
}

void Ball::InverseVertical() {
    vector.yVector.direction = -vector.yVector.direction;
}

Vector &Ball::GetVector() {
    return vector;
}

